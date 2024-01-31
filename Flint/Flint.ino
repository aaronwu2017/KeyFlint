#include <Arduino.h>
#include <lvgl.h>

#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "FT6236.h"

extern "C" {
#include "random.h"
}
#include "KeyManager.h"
#include <ui.h>
#include "Bitcoin.h"
#include "PSBT.h"
#include "Conversion.h"
#include "Hash.h"
//----ur

#include "crc32.h"
#include "xoshiro256.hpp"
#include "utils.hpp"
#include "random-sampler.hpp"
#include "fountain-encoder.hpp"
#include "fountain-utils.hpp"
#include "test-utils.hpp"
#include <vector>
#include <array>
#include <string>
#include <assert.h>
#include <algorithm> 
//---
const int i2c_touch_addr = TOUCH_I2C_ADD;
#define LCD_BL 46
#define SDA_FT6236 38
#define SCL_FT6236 39

#include "CurrentPSBT.h"
#define SCK       42                  // SCK on SPI3
#define MISO      41                  // MISO on SPI3 
#define MOSI      2                   // MOSI on SPI3
#define CS        1                   // 
#include <SPI.h>
#include "FS.h"
#include <SD.h>
#define TX1           38 
#define RX1           39    
class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ILI9488 _panel_instance;
  lgfx::Bus_Parallel16 _bus_instance;

public:
  LGFX(void) {
    {
    auto cfg = _bus_instance.config();
        cfg.port = 0;
        cfg.freq_write = 80000000;
        cfg.pin_wr = 18;
        cfg.pin_rd = 48;
        cfg.pin_rs = 45;

        cfg.pin_d0 = 47;
        cfg.pin_d1 = 21;
        cfg.pin_d2 = 14;
        cfg.pin_d3 = 13;
        cfg.pin_d4 = 12;
        cfg.pin_d5 = 11;
        cfg.pin_d6 = 10;
        cfg.pin_d7 = 9;
        cfg.pin_d8 = 3;
        cfg.pin_d9 = 8;
        cfg.pin_d10 = 16;
        cfg.pin_d11 = 15;
        cfg.pin_d12 = 7;
        cfg.pin_d13 = 6;
        cfg.pin_d14 = 5;
        cfg.pin_d15 = 4;
        _bus_instance.config(cfg);
        _panel_instance.setBus(&_bus_instance);
    }

    {
        auto cfg = _panel_instance.config();

        cfg.pin_cs = -1;
        cfg.pin_rst = -1;
        cfg.pin_busy = -1;
        cfg.memory_width = 320;
        cfg.memory_height = 480;
        cfg.panel_width = 320;
        cfg.panel_height = 480;
        cfg.offset_x = 0;
        cfg.offset_y = 0;
        cfg.offset_rotation = 2;
        cfg.dummy_read_pixel = 8;
        cfg.dummy_read_bits = 1;
        cfg.readable = true; 
        cfg.invert = false;
        cfg.rgb_order = false;
        cfg.dlen_16bit = true;
        cfg.bus_shared = true;
        _panel_instance.config(cfg);
    }
    setPanel(&_panel_instance);
  }
};

LGFX tft;

static const uint16_t screenWidth = 480;
static const uint16_t screenHeight = 320;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * screenHeight / 5];

// ... (other functions like my_disp_flush, my_touchpad_read, touch_init)

/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
  uint32_t w = ( area->x2 - area->x1 + 1 );
  uint32_t h = ( area->y2 - area->y1 + 1 );

  tft.startWrite();
  tft.setAddrWindow( area->x1, area->y1, w, h );
  tft.writePixels((lgfx::rgb565_t *)&color_p->full, w * h);
  tft.endWrite();

  lv_disp_flush_ready( disp );
}

void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
  int pos[2] = {0, 0};

  ft6236_pos(pos);
  if (pos[0] > 0 && pos[1] > 0)
  {
    data->state = LV_INDEV_STATE_PR;
    //    data->point.x = tft.width()-pos[1];
    //    data->point.y = pos[0];
    data->point.x = tft.width() - pos[1];
    data->point.y = pos[0];
    Serial.printf("x-%d,y-%d\n", data->point.x, data->point.y);
  }
  else {
    data->state = LV_INDEV_STATE_REL;
  }
}


void touch_init()
{
  // I2C init
  Wire.begin(SDA_FT6236, SCL_FT6236);
  byte error, address;

  Wire.beginTransmission(i2c_touch_addr);
  error = Wire.endTransmission();

  if (error == 0)
  {
    Serial.print("I2C device found at address 0x");
    Serial.print(i2c_touch_addr, HEX);
    Serial.println("  !");
  }
  else if (error == 4)
  {
    Serial.print("Unknown error at address 0x");
    Serial.println(i2c_touch_addr, HEX);
  }
}
void setup() {
  Serial.begin(115200); // prepare for possible serial debug
  tft.begin(); // TFT init
  tft.setRotation(1); // Landscape orientation, flipped
  tft.fillScreen(TFT_BLACK);
  pinMode(LCD_BL, OUTPUT);
  digitalWrite(LCD_BL, HIGH);
  //touch_init();
  
  lv_init();
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * screenHeight / 5);

  // Initialize the display
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  // Initialize the (dummy) input device driver
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  ui_init();
  //initializeEncoder();
  initializeDecoder();

  

  SPI.begin(SCK, MISO, MOSI, -1);
  if (!SD.begin(CS)) {
    while (!SD.begin(CS)) {
      Serial.println(F("error with SPI!"));
      delay(500);
    }
  }
  Serial1.begin(115200, SERIAL_8N1, RX1, TX1);      
  Serial.println("Setup done");

}

void loop() {
  lv_timer_handler(); // let the GUI do its work
  delay(5);

      CurrentPSBT& currentPSBT = CurrentPSBT::getInstance();

   // Check the status of startExporting
    if (currentPSBT.getStartExporting()) {
    std::string str = currentPSBT.getNextPart();
    showPSBT(str);

      delay(100);
    } else if (currentPSBT.getStartReceiving()){
  
      if (!currentPSBT.isDecodeSuccess ()) {

           if (Serial1.available() > 0) {
              String tempVal = "";
              while (Serial1.available() > 0) {
                tempVal += char(Serial1.read());
              }
              Serial.println(tempVal);
               currentPSBT.receivePart(tempVal.c_str());
            }
                     
        //printByteVector(decoder.result_ur().cbor());
      }else{
        //next screen
        
      
        printByteVector(  currentPSBT.getDecodedUR().cbor());
        ur::ByteVector psbtURFormat = currentPSBT.getDecodedUR().cbor();
std::vector<uint8_t> prefix = {0x59};
//CBOR prefix 58-> one byte, 00x00 to 0xFF (0 to 255 in decimal).
//  59->0x0100 to 0xFFFF (256 to 65,535 in decimal).  5A->0x00010000 to 0xFFFFFFFF (65,536 to 4,294,967,295 in decimal).
      if (psbtURFormat.size() >= prefix.size() && 
    std::equal(prefix.begin(), prefix.end(), psbtURFormat.begin())) {
    // Create a new string from the vector, starting from the 4th byte
    std::string resultString(psbtURFormat.begin() + 3, psbtURFormat.end());
    
    std::string psbtURFormatHex = ur::data_to_hex(psbtURFormat);
   Serial.println(psbtURFormatHex.c_str());
   std::string strippedString = psbtURFormatHex.substr(6); 
        PSBT psbt ;
      
        psbt.parse(strippedString.c_str());  
           CurrentPSBT::getInstance().setPSBT(psbt);
              Serial.println(resultString.c_str());
             Serial.println(psbt);
         }
    
      CurrentPSBT::getInstance().setStartReceiving(false);
      }
       
    }



      delay(100);





}

// void handlePassPhrase(){

// }

// void signAndExport(){
// Encoder en = new 
//   auto ur = make_message_ur(256);
//     auto encoder = ur::UREncoder(ur, 30);
//     ur::StringVector parts;
//     for(int i = 0; i < 20; i++) {
//         parts.push_back(encoder.next_part());
//     }    
// }

 void initializeEncoder(){

 std::string hex = "70736274FF0100710200000001ED84DAEC9AC7339866EBDD783D2EEF73D852B19727D12CFBA452C5B4C55DACA60100000000FDFFFFFF02AE7F020000000000160014FD15359F2FB4535B53EADD5D8B22419DC8F51DB69CAD0000000000001600149715AAF35C6CABC6AA7B74A21BC3C6A5203D4463BC0D0C004F010488B21E0343B8F0F08000000085B6BA9FD5EFC1E94A2EF228A69F2A0F3227BD09E99B3F93C94AC82CBD805554029359AF864F4EED5EEAA3A98C3A3E719E806153BCFEE162E352BB3F4AAA2D6F30107E1B62C25400008000000080000000800001011F0241030000000000160014DB78D10BC82CB54A8CBE0EAB10D5B6F5FA4D92F10103040100000022060348C5CD76FEE2E91017333FFC35F27EB895D1146DA0A1DDB6C38CB69361ECF734187E1B62C25400008000000080000000800100000001000000002202030FA9F933DBDB87540324D501EC5695D7E1CFAB40E037A26FE3EE398AA5CB2F58187E1B62C254000080000000800000008001000000020000000000";

  ur::ByteVector message = hexStringToByteVector(hex);
  ur::ByteVector cbor;
  ur::CborLite::encodeBytes(cbor, message);
  auto ur =  ur::UR("crypto-psbt", cbor);
auto encoder = std::make_unique<ur::UREncoder>(ur, 10);
CurrentPSBT::getInstance().setEncoder(std::move(encoder));
CurrentPSBT::getInstance().setStartExporting(true);

}

 void initializeDecoder(){


auto decoder = std::make_unique<ur::URDecoder>();


CurrentPSBT::getInstance().setDecoder(std::move(decoder));
CurrentPSBT::getInstance().setStartReceiving(true);

}

ur::ByteVector hexStringToByteVector(const std::string& hex) {
    std::vector<uint8_t> bytes;

    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        uint8_t byte = static_cast<uint8_t>(std::stoul(byteString, nullptr, 16));
        bytes.push_back(byte);
    }

    return bytes;
}
void printByteVector(const ur::ByteVector& vec) {
    for (uint8_t byte : vec) {
        // Print as a hexadecimal number
        if (byte < 16) Serial.print("0"); // Print a leading zero for numbers less than 16 (0x10)
        Serial.print(byte, HEX); // Print the byte in hexadecimal format
        
    }
    Serial.println(); // New line after printing the vector
}