#include <Arduino.h>
#include <lvgl.h>

#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "FT6236.h"

// extern "C" {
// #include "random.h"
// }
#include "KeyManager.h"
#include <ui.h>
#include "Bitcoin.h"
#include "PSBT.h"
#include "Conversion.h"
#include "Hash.h"
//----ur


#include "test-utils.hpp"

//---

const int i2c_touch_addr = TOUCH_I2C_ADD;
#define LCD_BL 46
#define SDA_FT6236 38
#define SCL_FT6236 39
//-----
#include "CurrentPSBT.h"
#define RX1           40 
#define TX1           -1 

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
  Serial1.begin(115200, SERIAL_8N1, RX1, TX1); 
  Serial.println("Setup done");

}

void loop() {
  // Serial.print("Free heap memory: ");
  // Serial.println(ESP.getFreeHeap());
  // UBaseType_t uxHighWaterMark;
  // uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);

  // Serial.print("Minimum free stack for loop task: ");
  // Serial.println(uxHighWaterMark * sizeof(portSTACK_TYPE)); // Convert to bytes

  lv_timer_handler(); // let the GUI do its work
  delay(5);

  CurrentPSBT& currentPSBT = CurrentPSBT::getInstance();
  //Serial.println(currentPSBT.getStartExporting());
 //
    // Check the status of startExporting
    if (currentPSBT.getStartExporting()) {
        encoderActivity();
     
    } else if (currentPSBT.getStartReceiving()) {
      decoderActivity();
    }
}

// void handlePassPhrase(){

// }


