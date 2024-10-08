// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_Screen117_screen_init(void)
{
ui_Screen117 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Screen117, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Screen117, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Screen117, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Button2228 = lv_btn_create(ui_Screen117);
lv_obj_set_width( ui_Button2228, 47);
lv_obj_set_height( ui_Button2228, 49);
lv_obj_set_x( ui_Button2228, -212 );
lv_obj_set_y( ui_Button2228, -132 );
lv_obj_set_align( ui_Button2228, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Button2228, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_Button2228, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Button2228, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Button2228, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_color(ui_Button2228, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_shadow_opa(ui_Button2228, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Label118 = lv_label_create(ui_Screen117);
lv_obj_set_width( ui_Label118, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label118, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label118, -4 );
lv_obj_set_y( ui_Label118, -89 );
lv_obj_set_align( ui_Label118, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label118,"Private Key");
lv_obj_add_state( ui_Label118, LV_STATE_PRESSED );     /// States
lv_obj_set_style_text_color(ui_Label118, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label118, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Label118, &lv_font_montserrat_18, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ImgButton118 = lv_imgbtn_create(ui_Screen117);
lv_imgbtn_set_src(ui_ImgButton118, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_white_background_resized_25x20_png, NULL);
lv_obj_set_height( ui_ImgButton118, 26);
lv_obj_set_width( ui_ImgButton118, LV_SIZE_CONTENT);  /// 1
lv_obj_set_x( ui_ImgButton118, lv_pct(-45) );
lv_obj_set_y( ui_ImgButton118, lv_pct(-40) );
lv_obj_set_align( ui_ImgButton118, LV_ALIGN_CENTER );

lv_obj_add_event_cb(ui_Button2228, ui_event_Button2228, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_ImgButton118, ui_event_ImgButton118, LV_EVENT_ALL, NULL);

}
