// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_Screen2_screen_init(void)
{
ui_Screen2 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Screen2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Screen2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Screen2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Screen2, &lv_font_montserrat_36, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Label3 = lv_label_create(ui_Screen2);
lv_obj_set_width( ui_Label3, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label3, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label3, lv_pct(0) );
lv_obj_set_y( ui_Label3, lv_pct(-42) );
lv_obj_set_align( ui_Label3, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label3,"Back up your seed");
lv_obj_set_style_text_color(ui_Label3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label3, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Label3, &lv_font_montserrat_30, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Roller2 = lv_roller_create(ui_Screen2);
lv_roller_set_options( ui_Roller2, "24.question\n18.daughter", LV_ROLLER_MODE_NORMAL );
lv_obj_set_width( ui_Roller2, lv_pct(38));
lv_obj_set_height( ui_Roller2, lv_pct(60));
lv_obj_set_y( ui_Roller2, -19 );
lv_obj_set_x( ui_Roller2, lv_pct(-31) );
lv_obj_set_align( ui_Roller2, LV_ALIGN_CENTER );
lv_obj_set_style_text_font(ui_Roller2, &lv_font_montserrat_24, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Panel3 = lv_obj_create(ui_Screen2);
lv_obj_set_width( ui_Panel3, lv_pct(60));
lv_obj_set_height( ui_Panel3, lv_pct(60));
lv_obj_set_x( ui_Panel3, lv_pct(19) );
lv_obj_set_y( ui_Panel3, lv_pct(-6) );
lv_obj_set_align( ui_Panel3, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Panel3, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label13 = lv_label_create(ui_Panel3);
lv_obj_set_width( ui_Label13, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label13, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label13, 0 );
lv_obj_set_y( ui_Label13, -10 );
lv_obj_set_align( ui_Label13, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label13,"Decimal: 1932\nBinary: 00000000000");
lv_obj_set_style_text_font(ui_Label13, &lv_font_montserrat_24, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Button7 = lv_btn_create(ui_Screen2);
lv_obj_set_height( ui_Button7, 66);
lv_obj_set_width( ui_Button7, lv_pct(76));
lv_obj_set_x( ui_Button7, 14 );
lv_obj_set_y( ui_Button7, 120 );
lv_obj_set_align( ui_Button7, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Button7, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_Button7, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Button7, lv_color_hex(0xAD9999), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Button7, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_radius(ui_Button7, 45, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_bg_color(ui_Button7, lv_color_hex(0x6C6C6C), LV_PART_MAIN | LV_STATE_PRESSED );
lv_obj_set_style_bg_opa(ui_Button7, 255, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_bg_grad_color(ui_Button7, lv_color_hex(0x6D6D6D), LV_PART_MAIN | LV_STATE_PRESSED );
lv_obj_set_style_bg_main_stop(ui_Button7, 0, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_bg_grad_stop(ui_Button7, 255, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_bg_grad_dir(ui_Button7, LV_GRAD_DIR_VER, LV_PART_MAIN| LV_STATE_PRESSED);

ui_Label11 = lv_label_create(ui_Button7);
lv_obj_set_width( ui_Label11, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label11, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label11, 0 );
lv_obj_set_y( ui_Label11, -1 );
lv_obj_set_align( ui_Label11, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label11,"OK, I wrote it down");
lv_obj_add_state( ui_Label11, LV_STATE_PRESSED );     /// States
lv_obj_set_style_text_color(ui_Label11, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label11, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Label11, &lv_font_montserrat_30, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Label7 = lv_label_create(ui_Screen2);
lv_obj_set_width( ui_Label7, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label7, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label7, -326 );
lv_obj_set_y( ui_Label7, -214 );
lv_obj_set_align( ui_Label7, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label7,"<back");
lv_obj_add_state( ui_Label7, LV_STATE_PRESSED );     /// States
lv_obj_set_style_text_color(ui_Label7, lv_color_hex(0xFF7129), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label7, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Label7, &lv_font_montserrat_30, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_Roller2, ui_event_Roller2, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Button7, ui_event_Button7, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Label7, ui_event_Label7, LV_EVENT_ALL, NULL);

}
