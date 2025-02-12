// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_deplay
void ui_deplay_screen_init(void);
lv_obj_t *ui_deplay;
void ui_event_wificonfigbt( lv_event_t * e);
lv_obj_t *ui_wificonfigbt;
lv_obj_t *ui_led1;
lv_obj_t *ui_led2;
lv_obj_t *ui_led3;
lv_obj_t *ui_led5;
lv_obj_t *ui_Bar1;
lv_obj_t *ui_led4;
lv_obj_t *ui_Image2;
void ui_event_Buttondow( lv_event_t * e);
lv_obj_t *ui_Buttondow;
void ui_event_Buttonup( lv_event_t * e);
lv_obj_t *ui_Buttonup;
void ui_event_settimg1( lv_event_t * e);
lv_obj_t *ui_settimg1;
lv_obj_t *ui_Label2;
void ui_event_settimg2( lv_event_t * e);
lv_obj_t *ui_settimg2;
lv_obj_t *ui_Label1;
void ui_event_Switch2( lv_event_t * e);
lv_obj_t *ui_Switch2;
lv_obj_t *ui_Label3;
lv_obj_t *ui_Label6;
lv_obj_t *ui_Label7;
lv_obj_t *ui_Label8;
lv_obj_t *ui_Label9;
lv_obj_t *ui_Image3;


// SCREEN: ui_swifiseting
void ui_swifiseting_screen_init(void);
void ui_event_swifiseting( lv_event_t * e);
lv_obj_t *ui_swifiseting;
lv_obj_t *ui_wifiseting;
void ui_event_Buttonbk1( lv_event_t * e);
lv_obj_t *ui_Buttonbk1;
void ui_event_Dropdown1( lv_event_t * e);
lv_obj_t *ui_Dropdown1;
void ui_event_TextArea5( lv_event_t * e);
lv_obj_t *ui_TextArea5;
lv_obj_t *ui_Ver;
void ui_event_Slider3( lv_event_t * e);
lv_obj_t *ui_Slider3;
lv_obj_t *ui_Label12;
lv_obj_t *ui_Label13;
void ui_event_Keyboard2( lv_event_t * e);
lv_obj_t *ui_Keyboard2;


// SCREEN: ui_stimeseting
void ui_stimeseting_screen_init(void);
lv_obj_t *ui_stimeseting;
void ui_event_Buttonbk( lv_event_t * e);
lv_obj_t *ui_Buttonbk;
lv_obj_t *ui_Checkbox2;
lv_obj_t *ui_Checkbox1;
lv_obj_t *ui_Checkbox3;
lv_obj_t *ui_Checkbox4;
lv_obj_t *ui_Checkbox5;
lv_obj_t *ui_Checkbox6;
lv_obj_t *ui_Checkbox7;
void ui_event_TextArea2( lv_event_t * e);
lv_obj_t *ui_TextArea2;
void ui_event_TextArea1( lv_event_t * e);
lv_obj_t *ui_TextArea1;
lv_obj_t *ui_Label4;
void ui_event_TextArea3( lv_event_t * e);
lv_obj_t *ui_TextArea3;
void ui_event_TextArea4( lv_event_t * e);
lv_obj_t *ui_TextArea4;
lv_obj_t *ui_Label5;
void ui_event_Keyboard1( lv_event_t * e);
lv_obj_t *ui_Keyboard1;
lv_obj_t *ui_Label10;
lv_obj_t *ui_Label11;
lv_obj_t *ui____initial_actions0;
const lv_img_dsc_t *ui_imgset_[1] = {&ui_img_11_png};
const lv_img_dsc_t *ui_imgset_693852941[1] = {&ui_img_1711361369};
const lv_img_dsc_t *ui_imgset_459866275[1] = {&ui_img_1986391116};
const lv_img_dsc_t *ui_imgset_filter_[1] = {&ui_img_filter_2_png};
const lv_img_dsc_t *ui_imgset_1777267941[4] = {&ui_img_602825187, &ui_img_602820839, &ui_img_602819814, &ui_img_602835949};

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_wificonfigbt( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_PRESSED) {
      _ui_screen_change( &ui_swifiseting, LV_SCR_LOAD_ANIM_MOVE_LEFT, 500, 0, &ui_swifiseting_screen_init);
}
}
void ui_event_Buttondow( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_PRESSED) {
      fandoawe( e );
}
}
void ui_event_Buttonup( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      fanupupup( e );
}
}
void ui_event_settimg1( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_PRESSED) {
      _ui_screen_change( &ui_stimeseting, LV_SCR_LOAD_ANIM_MOVE_LEFT, 500, 0, &ui_stimeseting_screen_init);
}
}
void ui_event_settimg2( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      set_mode( e );
}
}
void ui_event_Switch2( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      SW_on_off_time( e );
}
}
void ui_event_swifiseting( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_SCREEN_LOADED) {
      wifi_scanning( e );
}
}
void ui_event_Buttonbk1( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_PRESSED) {
      _ui_screen_change( &ui_deplay, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 500, 0, &ui_deplay_screen_init);
      wifi_save_ssid_( e );
}
}
void ui_event_Dropdown1( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      SSIDWIFIXX( e );
}
}
void ui_event_TextArea5( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_PRESSED) {
      _ui_flag_modify( ui_Keyboard2, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
      _ui_keyboard_set_target(ui_Keyboard2,  ui_TextArea5);
}
}
void ui_event_Slider3( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      _ui_slider_set_text_value( ui_Label13, target, "", "");
}
}
void ui_event_Keyboard2( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_READY) {
      _ui_flag_modify( ui_Keyboard2, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
      wificonnectin( e );
}
}
void ui_event_Buttonbk( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_PRESSED) {
      _ui_screen_change( &ui_deplay, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 500, 0, &ui_deplay_screen_init);
      Timeseting_p_ep( e );
}
}
void ui_event_TextArea2( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_PRESSED) {
      _ui_flag_modify( ui_Keyboard1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
      _ui_keyboard_set_target(ui_Keyboard1,  ui_TextArea2);
}
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      M_limi_num_on( e );
}
}
void ui_event_TextArea1( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_PRESSED) {
      _ui_flag_modify( ui_Keyboard1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
      _ui_keyboard_set_target(ui_Keyboard1,  ui_TextArea1);
}
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      H_limi_num_on( e );
}
}
void ui_event_TextArea3( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_PRESSED) {
      _ui_flag_modify( ui_Keyboard1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
      _ui_keyboard_set_target(ui_Keyboard1,  ui_TextArea3);
}
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      H_limi_num_off( e );
}
}
void ui_event_TextArea4( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_PRESSED) {
      _ui_flag_modify( ui_Keyboard1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
      _ui_keyboard_set_target(ui_Keyboard1,  ui_TextArea4);
}
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      M_limi_num_off( e );
}
}
void ui_event_Keyboard1( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_READY) {
      _ui_flag_modify( ui_Keyboard1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
}
}

///////////////////// SCREENS ////////////////////

void ui_init( void )
{LV_EVENT_GET_COMP_CHILD = lv_event_register_id();

lv_disp_t *dispp = lv_disp_get_default();
lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
lv_disp_set_theme(dispp, theme);
ui_deplay_screen_init();
ui_swifiseting_screen_init();
ui_stimeseting_screen_init();
ui____initial_actions0 = lv_obj_create(NULL);
lv_disp_load_scr( ui_deplay);
}
