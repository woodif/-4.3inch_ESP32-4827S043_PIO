// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_swifiseting_screen_init(void)
{
ui_swifiseting = lv_obj_create(NULL);
lv_obj_clear_flag( ui_swifiseting, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_wifiseting = lv_label_create(ui_swifiseting);
lv_obj_set_width( ui_wifiseting, LV_SIZE_CONTENT);  /// 9
lv_obj_set_height( ui_wifiseting, LV_SIZE_CONTENT);   /// 2
lv_obj_set_x( ui_wifiseting, 3 );
lv_obj_set_y( ui_wifiseting, -100 );
lv_obj_set_align( ui_wifiseting, LV_ALIGN_CENTER );
lv_label_set_text(ui_wifiseting,"wifi seting");
lv_obj_set_style_text_font(ui_wifiseting, &ui_font_Font20, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Buttonbk1 = lv_btn_create(ui_swifiseting);
lv_obj_set_width( ui_Buttonbk1, 50);
lv_obj_set_height( ui_Buttonbk1, 50);
lv_obj_set_x( ui_Buttonbk1, -212 );
lv_obj_set_y( ui_Buttonbk1, -107 );
lv_obj_set_align( ui_Buttonbk1, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Buttonbk1, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_Buttonbk1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Buttonbk1, lv_color_hex(0x06D7F3), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Buttonbk1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_img_src( ui_Buttonbk1, &ui_img_1711361369, LV_PART_MAIN | LV_STATE_DEFAULT );

ui_Dropdown1 = lv_dropdown_create(ui_swifiseting);
lv_dropdown_set_options( ui_Dropdown1, "Scan start\n2\n5\n6\n7\n8\n" );
lv_obj_set_width( ui_Dropdown1, 165);
lv_obj_set_height( ui_Dropdown1, LV_SIZE_CONTENT);   /// 20
lv_obj_set_x( ui_Dropdown1, -111 );
lv_obj_set_y( ui_Dropdown1, -58 );
lv_obj_set_align( ui_Dropdown1, LV_ALIGN_CENTER );
lv_obj_add_state( ui_Dropdown1, LV_STATE_PRESSED );     /// States
lv_obj_add_flag( ui_Dropdown1, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_Dropdown1, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE );    /// Flags
lv_obj_set_scroll_dir(ui_Dropdown1, LV_DIR_TOP);



ui_TextArea5 = lv_textarea_create(ui_swifiseting);
lv_obj_set_width( ui_TextArea5, 165);
lv_obj_set_height( ui_TextArea5, LV_SIZE_CONTENT);   /// 41
lv_obj_set_x( ui_TextArea5, 113 );
lv_obj_set_y( ui_TextArea5, -55 );
lv_obj_set_align( ui_TextArea5, LV_ALIGN_CENTER );
lv_textarea_set_max_length(ui_TextArea5,12);
lv_textarea_set_placeholder_text(ui_TextArea5,"Password");
lv_textarea_set_one_line(ui_TextArea5,true);



ui_Ver = lv_label_create(ui_swifiseting);
lv_obj_set_width( ui_Ver, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Ver, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Ver, 217 );
lv_obj_set_y( ui_Ver, 123 );
lv_obj_set_align( ui_Ver, LV_ALIGN_CENTER );
lv_label_set_text(ui_Ver,"V 0.0");
lv_obj_set_style_text_font(ui_Ver, &ui_font_kanit28, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Slider3 = lv_slider_create(ui_swifiseting);
lv_slider_set_range(ui_Slider3, 10,300);
lv_obj_set_width( ui_Slider3, 236);
lv_obj_set_height( ui_Slider3, 10);
lv_obj_set_x( ui_Slider3, 37 );
lv_obj_set_y( ui_Slider3, -3 );
lv_obj_set_align( ui_Slider3, LV_ALIGN_CENTER );


ui_Label12 = lv_label_create(ui_swifiseting);
lv_obj_set_width( ui_Label12, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label12, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label12, -142 );
lv_obj_set_y( ui_Label12, -4 );
lv_obj_set_align( ui_Label12, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label12,"Set time out");
lv_obj_set_style_text_font(ui_Label12, &ui_font_Font16, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Label13 = lv_label_create(ui_swifiseting);
lv_obj_set_width( ui_Label13, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label13, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label13, 175 );
lv_obj_set_y( ui_Label13, -4 );
lv_obj_set_align( ui_Label13, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label13,"0");

ui_Keyboard2 = lv_keyboard_create(ui_swifiseting);
lv_obj_set_width( ui_Keyboard2, 300);
lv_obj_set_height( ui_Keyboard2, 139);
lv_obj_set_x( ui_Keyboard2, 11 );
lv_obj_set_y( ui_Keyboard2, 41 );
lv_obj_set_align( ui_Keyboard2, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Keyboard2, LV_OBJ_FLAG_HIDDEN );   /// Flags
lv_obj_clear_flag( ui_Keyboard2, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE );    /// Flags

lv_obj_add_event_cb(ui_Buttonbk1, ui_event_Buttonbk1, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Dropdown1, ui_event_Dropdown1, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_TextArea5, ui_event_TextArea5, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Slider3, ui_event_Slider3, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Keyboard2, ui_event_Keyboard2, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_swifiseting, ui_event_swifiseting, LV_EVENT_ALL, NULL);

}