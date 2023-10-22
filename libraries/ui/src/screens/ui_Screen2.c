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
lv_obj_set_x( ui_Label3, 76 );
lv_obj_set_y( ui_Label3, -169 );
lv_obj_set_align( ui_Label3, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label3,"Back up your seed");
lv_obj_set_style_text_color(ui_Label3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label3, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Label3, &lv_font_montserrat_30, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Panel1 = lv_obj_create(ui_Screen2);
lv_obj_set_width( ui_Panel1, 287);
lv_obj_set_height( ui_Panel1, 53);
lv_obj_set_x( ui_Panel1, 100 );
lv_obj_set_y( ui_Panel1, 38 );
lv_obj_set_align( ui_Panel1, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Panel1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Panel1, lv_color_hex(0x6C6C6C), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Panel1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Panel5 = lv_obj_create(ui_Panel1);
lv_obj_set_width( ui_Panel5, 7);
lv_obj_set_height( ui_Panel5, 11);
lv_obj_set_x( ui_Panel5, 5 );
lv_obj_set_y( ui_Panel5, -2 );
lv_obj_set_align( ui_Panel5, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Panel5, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_Panel5, 11, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Panel4 = lv_obj_create(ui_Panel1);
lv_obj_set_width( ui_Panel4, 11);
lv_obj_set_height( ui_Panel4, 11);
lv_obj_set_x( ui_Panel4, -33 );
lv_obj_set_y( ui_Panel4, 1 );
lv_obj_set_align( ui_Panel4, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Panel4, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_Panel4, 11, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Panel6 = lv_obj_create(ui_Panel1);
lv_obj_set_width( ui_Panel6, 11);
lv_obj_set_height( ui_Panel6, 9);
lv_obj_set_x( ui_Panel6, 55 );
lv_obj_set_y( ui_Panel6, -3 );
lv_obj_set_align( ui_Panel6, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Panel6, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_Panel6, 11, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Panel7 = lv_obj_create(ui_Panel1);
lv_obj_set_width( ui_Panel7, 11);
lv_obj_set_height( ui_Panel7, 11);
lv_obj_set_x( ui_Panel7, 40 );
lv_obj_set_y( ui_Panel7, -3 );
lv_obj_set_align( ui_Panel7, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Panel7, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_Panel7, 11, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Panel7, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Panel7, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Panel8 = lv_obj_create(ui_Panel1);
lv_obj_set_width( ui_Panel8, 11);
lv_obj_set_height( ui_Panel8, 11);
lv_obj_set_x( ui_Panel8, -15 );
lv_obj_set_y( ui_Panel8, -2 );
lv_obj_set_align( ui_Panel8, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Panel8, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_Panel8, 11, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Panel8, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Panel8, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Panel9 = lv_obj_create(ui_Panel1);
lv_obj_set_width( ui_Panel9, 11);
lv_obj_set_height( ui_Panel9, 11);
lv_obj_set_x( ui_Panel9, -69 );
lv_obj_set_y( ui_Panel9, 0 );
lv_obj_set_align( ui_Panel9, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Panel9, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_Panel9, 11, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Panel9, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Panel9, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Panel2 = lv_obj_create(ui_Panel1);
lv_obj_set_width( ui_Panel2, 11);
lv_obj_set_height( ui_Panel2, 11);
lv_obj_set_x( ui_Panel2, -49 );
lv_obj_set_y( ui_Panel2, 0 );
lv_obj_set_align( ui_Panel2, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Panel2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_Panel2, 11, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Panel10 = lv_obj_create(ui_Panel1);
lv_obj_set_width( ui_Panel10, 11);
lv_obj_set_height( ui_Panel10, 11);
lv_obj_set_x( ui_Panel10, 21 );
lv_obj_set_y( ui_Panel10, -3 );
lv_obj_set_align( ui_Panel10, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Panel10, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_Panel10, 11, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Panel10, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Panel10, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Panel11 = lv_obj_create(ui_Panel1);
lv_obj_set_width( ui_Panel11, 11);
lv_obj_set_height( ui_Panel11, 9);
lv_obj_set_x( ui_Panel11, 81 );
lv_obj_set_y( ui_Panel11, -5 );
lv_obj_set_align( ui_Panel11, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Panel11, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_Panel11, 11, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Panel12 = lv_obj_create(ui_Panel1);
lv_obj_set_width( ui_Panel12, 11);
lv_obj_set_height( ui_Panel12, 10);
lv_obj_set_x( ui_Panel12, 116 );
lv_obj_set_y( ui_Panel12, -2 );
lv_obj_set_align( ui_Panel12, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Panel12, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_Panel12, 11, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Panel13 = lv_obj_create(ui_Panel1);
lv_obj_set_width( ui_Panel13, 11);
lv_obj_set_height( ui_Panel13, 11);
lv_obj_set_x( ui_Panel13, 102 );
lv_obj_set_y( ui_Panel13, -4 );
lv_obj_set_align( ui_Panel13, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Panel13, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_Panel13, 11, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Panel13, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Panel13, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Roller2 = lv_roller_create(ui_Screen2);
lv_roller_set_options( ui_Roller2, "1.word\n2.word\n3.word\n4.word\n5.word\n6.word\n7.word\n8.word\n9.word\n10.word\n12.word\n13.word\n14.word\n15.word\n16.word\n17.word\n18.word\n19.word\n20.word\n21.word", LV_ROLLER_MODE_NORMAL );
lv_obj_set_height( ui_Roller2, 261);
lv_obj_set_width( ui_Roller2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_x( ui_Roller2, -237 );
lv_obj_set_y( ui_Roller2, -55 );
lv_obj_set_align( ui_Roller2, LV_ALIGN_CENTER );

ui_Panel3 = lv_obj_create(ui_Screen2);
lv_obj_set_width( ui_Panel3, 373);
lv_obj_set_height( ui_Panel3, 98);
lv_obj_set_x( ui_Panel3, 88 );
lv_obj_set_y( ui_Panel3, -83 );
lv_obj_set_align( ui_Panel3, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Panel3, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label13 = lv_label_create(ui_Panel3);
lv_obj_set_width( ui_Label13, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label13, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label13, 2 );
lv_obj_set_y( ui_Label13, 1 );
lv_obj_set_align( ui_Label13, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label13,"Decimal: 1932\nBinary: 10010110010");
lv_obj_set_style_text_font(ui_Label13, &lv_font_montserrat_30, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Button7 = lv_btn_create(ui_Screen2);
lv_obj_set_height( ui_Button7, 78);
lv_obj_set_width( ui_Button7, lv_pct(82));
lv_obj_set_x( ui_Button7, 27 );
lv_obj_set_y( ui_Button7, 148 );
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

lv_obj_add_event_cb(ui_Button7, ui_event_Button7, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Label7, ui_event_Label7, LV_EVENT_ALL, NULL);

}
