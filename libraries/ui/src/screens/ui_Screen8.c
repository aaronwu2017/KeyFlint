// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_Screen8_screen_init(void)
{
ui_Screen8 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Screen8, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Screen8, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Screen8, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Button9 = lv_btn_create(ui_Screen8);
lv_obj_set_width( ui_Button9, lv_pct(80));
lv_obj_set_height( ui_Button9, lv_pct(20));
lv_obj_set_x( ui_Button9, lv_pct(0) );
lv_obj_set_y( ui_Button9, lv_pct(-6) );
lv_obj_set_align( ui_Button9, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Button9, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_Button9, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Button9, lv_color_hex(0xAD9999), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Button9, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_radius(ui_Button9, 45, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_bg_color(ui_Button9, lv_color_hex(0x6C6C6C), LV_PART_MAIN | LV_STATE_PRESSED );
lv_obj_set_style_bg_opa(ui_Button9, 255, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_bg_grad_color(ui_Button9, lv_color_hex(0x6D6D6D), LV_PART_MAIN | LV_STATE_PRESSED );
lv_obj_set_style_bg_main_stop(ui_Button9, 0, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_bg_grad_stop(ui_Button9, 255, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_bg_grad_dir(ui_Button9, LV_GRAD_DIR_VER, LV_PART_MAIN| LV_STATE_PRESSED);

ui_Label15 = lv_label_create(ui_Button9);
lv_obj_set_width( ui_Label15, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label15, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label15, 0 );
lv_obj_set_y( ui_Label15, -1 );
lv_obj_set_align( ui_Label15, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label15,"Default");
lv_obj_add_state( ui_Label15, LV_STATE_PRESSED );     /// States
lv_obj_set_style_text_color(ui_Label15, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label15, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Label15, &lv_font_montserrat_30, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Button10 = lv_btn_create(ui_Screen8);
lv_obj_set_width( ui_Button10, lv_pct(80));
lv_obj_set_height( ui_Button10, lv_pct(20));
lv_obj_set_x( ui_Button10, lv_pct(0) );
lv_obj_set_y( ui_Button10, lv_pct(15) );
lv_obj_set_align( ui_Button10, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Button10, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_Button10, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Button10, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Button10, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_color(ui_Button10, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_shadow_opa(ui_Button10, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_radius(ui_Button10, 45, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_bg_color(ui_Button10, lv_color_hex(0x6C6C6C), LV_PART_MAIN | LV_STATE_PRESSED );
lv_obj_set_style_bg_opa(ui_Button10, 255, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_bg_grad_color(ui_Button10, lv_color_hex(0x6D6D6D), LV_PART_MAIN | LV_STATE_PRESSED );
lv_obj_set_style_bg_main_stop(ui_Button10, 0, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_bg_grad_stop(ui_Button10, 255, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_bg_grad_dir(ui_Button10, LV_GRAD_DIR_VER, LV_PART_MAIN| LV_STATE_PRESSED);

ui_Label16 = lv_label_create(ui_Button10);
lv_obj_set_width( ui_Label16, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label16, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label16, 2 );
lv_obj_set_y( ui_Label16, -6 );
lv_obj_set_align( ui_Label16, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label16,"Add more entropy");
lv_obj_add_state( ui_Label16, LV_STATE_PRESSED );     /// States
lv_obj_set_style_text_color(ui_Label16, lv_color_hex(0xFF7129), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label16, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Label16, &lv_font_montserrat_30, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_Button9, ui_event_Button9, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Button10, ui_event_Button10, LV_EVENT_ALL, NULL);

}
