// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_Screen14_screen_init(void)
{
ui_Screen14 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Screen14, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Screen14, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Screen14, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ImgButton5 = lv_imgbtn_create(ui_Screen14);
lv_imgbtn_set_src(ui_ImgButton5, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_1882376574, NULL);
lv_obj_set_width( ui_ImgButton5, 53);
lv_obj_set_height( ui_ImgButton5, 53);
lv_obj_set_x( ui_ImgButton5, 189 );
lv_obj_set_y( ui_ImgButton5, -116 );
lv_obj_set_align( ui_ImgButton5, LV_ALIGN_CENTER );

ui_Label35 = lv_label_create(ui_Screen14);
lv_obj_set_width( ui_Label35, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label35, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label35, -97 );
lv_obj_set_y( ui_Label35, -63 );
lv_obj_set_align( ui_Label35, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label35,"export psbt");
lv_obj_add_state( ui_Label35, LV_STATE_PRESSED );     /// States
lv_obj_set_style_text_color(ui_Label35, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label35, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Label35, &lv_font_montserrat_24, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Button19 = lv_btn_create(ui_Screen14);
lv_obj_set_height( ui_Button19, 65);
lv_obj_set_width( ui_Button19, lv_pct(82));
lv_obj_set_x( ui_Button19, 12 );
lv_obj_set_y( ui_Button19, 94 );
lv_obj_set_align( ui_Button19, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Button19, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_Button19, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Button19, lv_color_hex(0xAD9999), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Button19, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_radius(ui_Button19, 45, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_bg_color(ui_Button19, lv_color_hex(0x6C6C6C), LV_PART_MAIN | LV_STATE_PRESSED );
lv_obj_set_style_bg_opa(ui_Button19, 255, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_bg_grad_color(ui_Button19, lv_color_hex(0x6D6D6D), LV_PART_MAIN | LV_STATE_PRESSED );
lv_obj_set_style_bg_main_stop(ui_Button19, 0, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_bg_grad_stop(ui_Button19, 255, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_bg_grad_dir(ui_Button19, LV_GRAD_DIR_VER, LV_PART_MAIN| LV_STATE_PRESSED);

ui_Label36 = lv_label_create(ui_Button19);
lv_obj_set_width( ui_Label36, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label36, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label36, -4 );
lv_obj_set_y( ui_Label36, 0 );
lv_obj_set_align( ui_Label36, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label36,"Back to home");
lv_obj_add_state( ui_Label36, LV_STATE_PRESSED );     /// States
lv_obj_set_style_text_color(ui_Label36, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label36, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Label36, &lv_font_montserrat_24, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_ImgButton5, ui_event_ImgButton5, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Button19, ui_event_Button19, LV_EVENT_ALL, NULL);

}
