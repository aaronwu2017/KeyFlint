#include <Arduino.h>
// #include <assert.h> 
// #include "crc32.h"
// #include "xoshiro256.hpp"
// #include "utils.hpp"
// #include "random-sampler.hpp"
// #include "fountain-encoder.hpp"
// #include "fountain-utils.hpp"
// #include "test-utils.hpp"
// #include <vector>
// #include <array>
// #include <string>
// #include <assert.h>
// #include <algorithm>


void showPSBT( std::string& str )
{
   // lv_obj_clean(ui_Screen112);
  //   lv_color_t bg_color = lv_palette_lighten(LV_PALETTE_LIGHT_BLUE, 5);
  //   lv_color_t fg_color = lv_palette_darken(LV_PALETTE_BLUE, 4);

  //   lv_obj_t * qr = lv_qrcode_create(ui_Screen112, 250, lv_color_hex3(0x000),lv_color_hex3(0xeef));
  //  // lv_qrcode_set_size(qr, 150);
  //  // lv_qrcode_set_dark_color(qr, fg_color);
  // //  lv_qrcode_set_light_color(qr, bg_color);


  
  //   lv_obj_center(qr);

  //   /*Add a border with bg_color*/
  //   lv_obj_set_style_border_color(qr, bg_color, 0);
  //   lv_obj_set_style_border_width(qr, 5, 0);
    

      lv_qrcode_update(qr,  str.c_str(), strlen(str.c_str()));
}




