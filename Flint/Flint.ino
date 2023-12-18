#include <Arduino.h>
#include <lvgl.h>
#define SHA256_LEN 32
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

String seedPhrase[24];

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
  touch_init();
  
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
  Serial.println("Setup done");

}

void loop() {
  lv_timer_handler(); // let the GUI do its work
  delay(5);
}

void generateSeed(lv_event_t *e) {
    uint8_t local_entropy_state[SHA256_LEN];
    random_start_collecting(local_entropy_state, SHA256_LEN);
    for (int i = 0; i < SHA256_LEN; i++) {
        Serial.print("entropy_state[");
        Serial.print(i);
        Serial.print("] = ");
        Serial.println(local_entropy_state[i], HEX); // Print in hexadecimal format
    }

    String entropy1 = "24";
    String tempSeedPhrase = generateMnemonic(24, local_entropy_state, 256);
    Serial.println(tempSeedPhrase);
    splitString(tempSeedPhrase);
    std::string newPassphrase = "newPassphrase";
    std::string seedPhraseArray[24];
    for (int i = 0; i < 24; ++i) {
    seedPhraseArray[i] = "TestPhrase" + std::to_string(i + 1);  // Creates "TestPhrase1", "TestPhrase2", etc.
    }
       Serial.println("finish initialize test array");
    KeyManager::getInstance().setValues(nullptr, nullptr,seedPhraseArray, &newPassphrase);
       Serial.println("finish setvalue KeyManager");
    String options = "";
    int wordNumber = 1; // Initialize word number counter

   // HDPrivateKey hd(tempSeedPhrase, "");
   
    String testTempSeedPhrase = "visual chair firm clock ability  chef  connect planet  benefit fork frown protect";
    HDPrivateKey hd(testTempSeedPhrase, "");
    Serial.println(hd);
//number each word in the 24 word seedphrase
    for (int i = 0; i < tempSeedPhrase.length(); i++) {
        if (i == 0 || tempSeedPhrase[i - 1] == ' ') { // Check for the start of a new word
            options += String(wordNumber) + ". "; // Append the word number and a period
            wordNumber++; // Increment the word number
        }

        if (tempSeedPhrase[i] == ' ') {
            options += '\n'; // Add a newline character instead of space
        } else {
            options += tempSeedPhrase[i]; // Add the current character
        }
    }

    const char *options_cStr = options.c_str();
    lv_roller_set_options(ui_Roller2, options_cStr, LV_ROLLER_MODE_NORMAL);

    String labelStr = seedPhrase[0];
   // lv_label_set_text(ui_Label28, labelStr.c_str());


     //
String psbt64 = "cHNidP8BAHECAAAAAUKAmWVFG/zLmhHQZ8Q8bQKCoNxxiurIcNZVhafCoLCyAAAAAAD9////AjksAAAAAAAAFgAUvDLbTPtQXj/JTiGj7HTRrvz8ASwiwQAAAAAAABYAFOq0zUDTkmdWzFLl+RydPI47QA4ReCIMAE8BBIiyHgPG2cycgAAAADKRxb1j69WGKYT3nQrjs2zcdlE3UiHFNYyGd3vysjMcAiVPCY671cdIpViKxJr/88kFWlty0jqxfwY8PfU3Tbu3EMh3/URUAACAAAAAgAAAAIAAAQEfN/cAAAAAAAAWABSUBvAKoN3uZMfqYvmU5pVYAoCj5QEDBAEAAAAiBgNa5FjqiQq3akaVNyAsPdho05JgUpccQlhll1wyKD/3FhjId/1EVAAAgAAAAIAAAACAAAAAAAEAAAAAACICAkjtpvsDgJ+za5zGXZjCZhj5fNVw8Uqc+AgQItHhEYiTGMh3/URUAACAAAAAgAAAAIABAAAAAAAAAAA=";
 Serial.println(psbt64);
PSBT psbt;
psbt.parseBase64(psbt64);
Serial.println("Transactions details:");
Serial.println("Outputs:");
// going through all outputs
for(int i=0; i<psbt.tx.outputsNumber; i++){
  Serial.print(psbt.tx.txOuts[i].address(&Mainnet));
  Serial.print(" -> ");
  // You can also use .btcAmount() function that returns a float in whole Bitcoins
  Serial.print(int(psbt.tx.txOuts[i].amount));
  Serial.println(" sat");
}
Serial.print("Fee: ");
// Arduino can't print 64-bit ints so we need to convert it to int
Serial.print(int(psbt.fee()));
Serial.println(" sat");
  Serial.println(psbt);
    Serial.println("========");
      Serial.println(psbt.toString());
            Serial.println(  psbt.toBase64());
  psbt.sign(hd);
   Serial.println(  psbt.toBase64());
  //
}
//get currect selected seed word in the UI roller
void getSelectedSeedWord(lv_event_t *e) {
    int wordIndex = lv_roller_get_selected(ui_Roller2);

    // Convert integer to string
    String wordIndexStr = String(wordIndex);

    // Concatenate with your desired text
    String labelStr = seedPhrase[wordIndex];

    // Set the label's text
    // lv_label_set_text(ui_Label28, labelStr.c_str());




    const std::string* mySeedPhrase = KeyManager::getInstance().getSeedPhrase();

// Now mySeedPhrase points to the first element of the seedPhrase array
// You can access individual phrases like this:

  Serial.println("test start");
    Serial.println(mySeedPhrase[wordIndex].c_str());
     Serial.println("test done");

}
//split seedphrase String into array of 24 strings for displaying information individually
void splitString(String str) {
    int wordIndex = 0;
    int startPos = 0;

    for (int i = 0; i < str.length(); i++) {
        if (str.charAt(i) == ' ' || i == str.length() - 1) {
            // Add the last word if we're at the end of the string
            String word = (i == str.length() - 1) ? str.substring(startPos) : str.substring(startPos, i);
            seedPhrase[wordIndex++] = word;
            startPos = i + 1; // Set start position for next word

            if (wordIndex >= 24) {
                break; // Avoid going beyond the array size
            }
        }
    }
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