// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_stimeseting_screen_init(void)
{
ui_stimeseting = lv_obj_create(NULL);
lv_obj_clear_flag( ui_stimeseting, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_stimeseting, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_stimeseting, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Buttonbk = lv_btn_create(ui_stimeseting);
lv_obj_set_width( ui_Buttonbk, 50);
lv_obj_set_height( ui_Buttonbk, 50);
lv_obj_set_x( ui_Buttonbk, -212 );
lv_obj_set_y( ui_Buttonbk, -107 );
lv_obj_set_align( ui_Buttonbk, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Buttonbk, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_Buttonbk, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Buttonbk, lv_color_hex(0x06D7F3), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Buttonbk, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_img_src( ui_Buttonbk, &ui_img_1711361369, LV_PART_MAIN | LV_STATE_DEFAULT );

ui_Checkbox2 = lv_checkbox_create(ui_stimeseting);
lv_checkbox_set_text(ui_Checkbox2,"Tue");
lv_obj_set_width( ui_Checkbox2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Checkbox2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Checkbox2, -56 );
lv_obj_set_y( ui_Checkbox2, 50 );
lv_obj_set_align( ui_Checkbox2, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Checkbox2, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags

ui_Checkbox1 = lv_checkbox_create(ui_stimeseting);
lv_checkbox_set_text(ui_Checkbox1,"Mon");
lv_obj_set_width( ui_Checkbox1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Checkbox1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Checkbox1, -124 );
lv_obj_set_y( ui_Checkbox1, 50 );
lv_obj_set_align( ui_Checkbox1, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Checkbox1, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags

ui_Checkbox3 = lv_checkbox_create(ui_stimeseting);
lv_checkbox_set_text(ui_Checkbox3,"Wed");
lv_obj_set_width( ui_Checkbox3, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Checkbox3, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Checkbox3, 16 );
lv_obj_set_y( ui_Checkbox3, 50 );
lv_obj_set_align( ui_Checkbox3, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Checkbox3, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags

ui_Checkbox4 = lv_checkbox_create(ui_stimeseting);
lv_checkbox_set_text(ui_Checkbox4,"Thu");
lv_obj_set_width( ui_Checkbox4, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Checkbox4, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Checkbox4, 86 );
lv_obj_set_y( ui_Checkbox4, 51 );
lv_obj_set_align( ui_Checkbox4, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Checkbox4, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags

ui_Checkbox5 = lv_checkbox_create(ui_stimeseting);
lv_checkbox_set_text(ui_Checkbox5,"Fri");
lv_obj_set_width( ui_Checkbox5, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Checkbox5, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Checkbox5, -83 );
lv_obj_set_y( ui_Checkbox5, 77 );
lv_obj_set_align( ui_Checkbox5, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Checkbox5, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags

ui_Checkbox6 = lv_checkbox_create(ui_stimeseting);
lv_checkbox_set_text(ui_Checkbox6,"Sat");
lv_obj_set_width( ui_Checkbox6, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Checkbox6, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Checkbox6, -15 );
lv_obj_set_y( ui_Checkbox6, 77 );
lv_obj_set_align( ui_Checkbox6, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Checkbox6, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags

ui_Checkbox7 = lv_checkbox_create(ui_stimeseting);
lv_checkbox_set_text(ui_Checkbox7,"Sun");
lv_obj_set_width( ui_Checkbox7, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Checkbox7, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Checkbox7, 56 );
lv_obj_set_y( ui_Checkbox7, 77 );
lv_obj_set_align( ui_Checkbox7, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Checkbox7, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags

ui_TextArea2 = lv_textarea_create(ui_stimeseting);
lv_obj_set_width( ui_TextArea2, 89);
lv_obj_set_height( ui_TextArea2, LV_SIZE_CONTENT);   /// 72
lv_obj_set_x( ui_TextArea2, -70 );
lv_obj_set_y( ui_TextArea2, -15 );
lv_obj_set_align( ui_TextArea2, LV_ALIGN_CENTER );
if ("0,1,2,3,4,5,6,7,8,9"=="") lv_textarea_set_accepted_chars(ui_TextArea2, NULL);
else lv_textarea_set_accepted_chars(ui_TextArea2, "0,1,2,3,4,5,6,7,8,9");
lv_textarea_set_max_length(ui_TextArea2,2);
lv_textarea_set_placeholder_text(ui_TextArea2," M");
lv_textarea_set_one_line(ui_TextArea2,true);
lv_obj_set_style_text_font(ui_TextArea2, &ui_font_Font48, LV_PART_MAIN| LV_STATE_DEFAULT);



ui_TextArea1 = lv_textarea_create(ui_stimeseting);
lv_obj_set_width( ui_TextArea1, 89);
lv_obj_set_height( ui_TextArea1, LV_SIZE_CONTENT);   /// 72
lv_obj_set_x( ui_TextArea1, -179 );
lv_obj_set_y( ui_TextArea1, -15 );
lv_obj_set_align( ui_TextArea1, LV_ALIGN_CENTER );
if ("0,1,2,3,4,5,6,7,8,9"=="") lv_textarea_set_accepted_chars(ui_TextArea1, NULL);
else lv_textarea_set_accepted_chars(ui_TextArea1, "0,1,2,3,4,5,6,7,8,9");
lv_textarea_set_max_length(ui_TextArea1,2);
lv_textarea_set_placeholder_text(ui_TextArea1," H");
lv_textarea_set_one_line(ui_TextArea1,true);
lv_obj_set_style_text_font(ui_TextArea1, &ui_font_Font48, LV_PART_MAIN| LV_STATE_DEFAULT);



ui_Label4 = lv_label_create(ui_stimeseting);
lv_obj_set_width( ui_Label4, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label4, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label4, -125 );
lv_obj_set_y( ui_Label4, -15 );
lv_obj_set_align( ui_Label4, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label4,":");
lv_obj_set_style_text_font(ui_Label4, &ui_font_Font48, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_TextArea3 = lv_textarea_create(ui_stimeseting);
lv_obj_set_width( ui_TextArea3, 89);
lv_obj_set_height( ui_TextArea3, LV_SIZE_CONTENT);   /// 72
lv_obj_set_x( ui_TextArea3, 72 );
lv_obj_set_y( ui_TextArea3, -15 );
lv_obj_set_align( ui_TextArea3, LV_ALIGN_CENTER );
if ("0,1,2,3,4,5,6,7,8,9"=="") lv_textarea_set_accepted_chars(ui_TextArea3, NULL);
else lv_textarea_set_accepted_chars(ui_TextArea3, "0,1,2,3,4,5,6,7,8,9");
lv_textarea_set_max_length(ui_TextArea3,2);
lv_textarea_set_placeholder_text(ui_TextArea3," H");
lv_textarea_set_one_line(ui_TextArea3,true);
lv_obj_set_style_text_font(ui_TextArea3, &ui_font_Font48, LV_PART_MAIN| LV_STATE_DEFAULT);



ui_TextArea4 = lv_textarea_create(ui_stimeseting);
lv_obj_set_width( ui_TextArea4, 89);
lv_obj_set_height( ui_TextArea4, LV_SIZE_CONTENT);   /// 72
lv_obj_set_x( ui_TextArea4, 178 );
lv_obj_set_y( ui_TextArea4, -15 );
lv_obj_set_align( ui_TextArea4, LV_ALIGN_CENTER );
if ("0,1,2,3,4,5,6,7,8,9"=="") lv_textarea_set_accepted_chars(ui_TextArea4, NULL);
else lv_textarea_set_accepted_chars(ui_TextArea4, "0,1,2,3,4,5,6,7,8,9");
lv_textarea_set_max_length(ui_TextArea4,2);
lv_textarea_set_placeholder_text(ui_TextArea4," M");
lv_textarea_set_one_line(ui_TextArea4,true);
lv_obj_set_style_text_font(ui_TextArea4, &ui_font_Font48, LV_PART_MAIN| LV_STATE_DEFAULT);



ui_Label5 = lv_label_create(ui_stimeseting);
lv_obj_set_width( ui_Label5, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label5, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label5, 125 );
lv_obj_set_y( ui_Label5, -15 );
lv_obj_set_align( ui_Label5, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label5,":");
lv_obj_set_style_text_font(ui_Label5, &ui_font_Font48, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Keyboard1 = lv_keyboard_create(ui_stimeseting);
lv_keyboard_set_mode(ui_Keyboard1,LV_KEYBOARD_MODE_NUMBER);
lv_obj_set_width( ui_Keyboard1, 323);
lv_obj_set_height( ui_Keyboard1, 102);
lv_obj_set_x( ui_Keyboard1, -3 );
lv_obj_set_y( ui_Keyboard1, 58 );
lv_obj_set_align( ui_Keyboard1, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Keyboard1, LV_OBJ_FLAG_HIDDEN );   /// Flags

ui_Label10 = lv_label_create(ui_stimeseting);
lv_obj_set_width( ui_Label10, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label10, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label10, -125 );
lv_obj_set_y( ui_Label10, -73 );
lv_obj_set_align( ui_Label10, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label10,"Time on");
lv_obj_set_style_text_font(ui_Label10, &ui_font_kanit28, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Label11 = lv_label_create(ui_stimeseting);
lv_obj_set_width( ui_Label11, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label11, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label11, 125 );
lv_obj_set_y( ui_Label11, -73 );
lv_obj_set_align( ui_Label11, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label11,"Time off");
lv_obj_set_style_text_font(ui_Label11, &ui_font_kanit28, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_Buttonbk, ui_event_Buttonbk, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_TextArea2, ui_event_TextArea2, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_TextArea1, ui_event_TextArea1, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_TextArea3, ui_event_TextArea3, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_TextArea4, ui_event_TextArea4, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Keyboard1, ui_event_Keyboard1, LV_EVENT_ALL, NULL);

}
