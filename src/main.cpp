#include <Arduino_GFX_Library.h>
#include "ui.h"
#include "WiFi.h"
#include "EEPROM.h"
#include <Ticker.h>
#include "time.h"
#include "RTClib.h"
#include <Adafruit_Sensor.h>
#include "Adafruit_SHT31.h"
#include "PMS.h"
#include "SD.h"
#include "SPI.h"
#include "PCF8574.h"

PMS pms(Serial1);
PMS::DATA data_s;

TaskHandle_t EEPROM_commit;
TaskHandle_t Read_Sensor;
TaskHandle_t data_sd_save;
SemaphoreHandle_t i2cMutex = NULL;

const char *ntpServer = "asia.pool.ntp.org";
const long gmtOffset_sec = 6 * 3600;
const int daylightOffset_sec = 3600;

RTC_DS3231 rtc;
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_SHT31 sht31 = Adafruit_SHT31();
PCF8574 PCF(0x39, &Wire);

struct tm timeinfo;

float Ver = 0.04;
#define EEPROM_SIZE 100
#define GFX_BL DF_GFX_BL // default backlight pin, you may replace DF_GFX_BL to actual backlight pin
#define TFT_BL 2
#define TOUCH_GT911_SCL 20
#define TOUCH_GT911_SDA 19
/* More dev device declaration: https://github.com/moononournation/Arduino_GFX/wiki/Dev-Device-Declaration */
#if defined(DISPLAY_DEV_KIT)
Arduino_GFX *gfx = create_default_Arduino_GFX();
#else /* !defined(DISPLAY_DEV_KIT) */

/* More data bus class: https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class */
// Arduino_DataBus *bus = create_default_Arduino_DataBus();

/* More display class: https://github.com/moononournation/Arduino_GFX/wiki/Display-Class */
// Arduino_GFX *gfx = new Arduino_ILI9341(bus, DF_GFX_RST, 0 /* rotation */, false /* IPS */);

Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
    GFX_NOT_DEFINED /* CS */, GFX_NOT_DEFINED /* SCK */, GFX_NOT_DEFINED /* SDA */,
    40 /* DE */, 41 /* VSYNC */, 39 /* HSYNC */, 42 /* PCLK */,
    45 /* R0 */, 48 /* R1 */, 47 /* R2 */, 21 /* R3 */, 14 /* R4 */,
    5 /* G0 */, 6 /* G1 */, 7 /* G2 */, 15 /* G3 */, 16 /* G4 */, 4 /* G5 */,
    8 /* B0 */, 3 /* B1 */, 46 /* B2 */, 9 /* B3 */, 1 /* B4 */
);
// option 1:
// ILI6485 LCD 480x272
Arduino_RPi_DPI_RGBPanel *gfx = new Arduino_RPi_DPI_RGBPanel(
    bus,
    480 /* width */, 0 /* hsync_polarity */, 8 /* hsync_front_porch */, 4 /* hsync_pulse_width */, 43 /* hsync_back_porch */,
    272 /* height */, 0 /* vsync_polarity */, 8 /* vsync_front_porch */, 4 /* vsync_pulse_width */, 12 /* vsync_back_porch */,
    1 /* pclk_active_neg */, 9000000 /* prefer_speed */, true /* auto_flush */);

#endif /* !defined(DISPLAY_DEV_KIT) */
/*******************************************************************************
 * End of Arduino_GFX setting
 ******************************************************************************/

#include "touch.h"

/* Change to your screen resolution */
static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;
static unsigned long last_ms;

String y_m_d_h_n = "";
String daysOfTheWeek[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
String monsOf[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
String WiFi_Networks_S[10];
int WiFi_Networks_ST = 0;
int WiFi_Networks_ST_b = 0;
int fan_ST_M = 0;
int fan_ST_A = 0;
int fan_out = 0;
int fan_out_b = 0;
int fan_mode = 0;
int time_mode = 0;
int day_st[7] = {0, 0, 0, 0, 0, 0, 0};
int wday_st = 0;
int time_on_off_st = 0;
int time_on_h = 0;
int time_on_m = 0;
int time_off_h = 0;
int time_off_m = 0;
int min_num_b = 0;
int EEPROM_commit_st = 0;
unsigned int PM2_5 = 0;
unsigned int PM10 = 0;
int Humidity = 0;
int Temperature = 0;
int hour_num = 0;
int hour_num_b = 0;
int second_num_x = 31;
uint32_t wdtx = 0;
uint32_t filter_reset = 0;
struct
{
   String ssid = "CMMC_test";
   String pass = "CMMC_test";
   String ID = "ID000";
   int day_st[7] = {0, 0, 0, 0, 0, 0, 0};
   int time_on_h = 0;
   int time_on_m = 1;
   int time_off_h = 0;
   int time_off_m = 2;
   int fan_mode = 0;
   int time_mode = 0;
   int fan_ST_M = 0;
   int time_on_off_st = 0;
   int fan_out = 0;
   int set_time_out = 0;
   uint16_t filter_co = 0;
} EEPROM_sd_config_txt;
/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
   uint32_t w = (area->x2 - area->x1 + 1);
   uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
   gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
   gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif

   lv_disp_flush_ready(disp);
}
int touch_xxxx = 0;
int touch_yyyy = 0;
bool touch_ssss = false;
uint32_t touch_time_out = 0;
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
   wdtx = 0;
   if (touch_ssss)
   {
      // if (touch_touched())
      // {
      data->point.x = touch_xxxx;
      data->point.y = touch_yyyy;
      data->state = LV_INDEV_STATE_PR;
      touch_time_out = 0;
      // Serial.println(touch_xxxx);
      // }
      // else if (touch_released())
      // {
      //    data->state = LV_INDEV_STATE_REL;
      // }
   }
   else
   {

      data->state = LV_INDEV_STATE_REL;
   }
}

void fandoawe(lv_event_t *e)
{
   if (fan_mode == 0)
   {
      fan_ST_M = fan_ST_M - 1;
      if (fan_ST_M <= 0)
         fan_ST_M = 0;
      EEPROM_sd_config_txt.fan_ST_M = fan_ST_M;
      EEPROM_commit_st = 1;
      // EEPROM.commit();
      // lv_bar_set_value(ui_Bar1, fan_ST_M, LV_ANIM_ON);
   }
}

void fanupupup(lv_event_t *e)
{
   if (fan_mode == 0)
   {
      fan_ST_M = fan_ST_M + 1;
      if (fan_ST_M >= 3)
         fan_ST_M = 3;

      EEPROM_sd_config_txt.fan_ST_M = fan_ST_M;
      EEPROM_commit_st = 1;
      // EEPROM.commit();
   }
}

void wifi_scanning(lv_event_t *e)
{

   WiFi.mode(WIFI_STA);
   WiFi.disconnect();
   delay(100);
   int n = WiFi.scanNetworks();

   String WiFi_Networks_row;
   if (n == 0)
   {
   }
   else
   {
      for (int i = 0; i < n; ++i)
      {
         if (i <= 9)
         {
            WiFi_Networks_row = WiFi_Networks_row + WiFi.SSID(i) + "\n";
            WiFi_Networks_S[i] = WiFi.SSID(i);
         }
         delay(10);
      }
      WiFi_Networks_row.trim();
      lv_dropdown_clear_options(ui_Dropdown1);
      lv_dropdown_set_options(ui_Dropdown1, WiFi_Networks_row.c_str());
      lv_dropdown_set_selected(ui_Dropdown1, 0);
   }
   WiFi.scanDelete();
}

void SSIDWIFIXX(lv_event_t *e)
{
}
void wificonnectin(lv_event_t *e)
{
   int selectedxxx = lv_dropdown_get_selected(ui_Dropdown1);
   String pass_x = String(lv_textarea_get_text(ui_TextArea5));
   String ssid_x = WiFi_Networks_S[selectedxxx];
   EEPROM_sd_config_txt.ssid = ssid_x;
   EEPROM_sd_config_txt.pass = pass_x;
   EEPROM_sd_config_txt.set_time_out = lv_slider_get_value(ui_Slider3);
   EEPROM_commit_st = 1;
   Serial.println(ssid_x + "," + pass_x);
   WiFi.begin(ssid_x.c_str(), pass_x.c_str());
}
void wifi_save_ssid_(lv_event_t *e)
{
   int selectedxxx = lv_dropdown_get_selected(ui_Dropdown1);
   String pass_x = String(lv_textarea_get_text(ui_TextArea5));
   String ssid_x = WiFi_Networks_S[selectedxxx];
   EEPROM_sd_config_txt.ssid = ssid_x;
   EEPROM_sd_config_txt.pass = pass_x;
   EEPROM_sd_config_txt.set_time_out = lv_slider_get_value(ui_Slider3);
   EEPROM_commit_st = 1;
   // EEPROM.writeString(0, ssid_x);
   // EEPROM.writeString(40, pass_x);
   // EEPROM.commit();
   Serial.println(ssid_x + "," + pass_x);
   WiFi.begin(ssid_x.c_str(), pass_x.c_str());
}
void eeprom_read()
{
   if (EEPROM_sd_config_txt.time_on_h < 24)
   {
      time_on_h = EEPROM_sd_config_txt.time_on_h;
      time_on_m = EEPROM_sd_config_txt.time_on_m;
      time_off_h = EEPROM_sd_config_txt.time_off_h;
      time_off_m = EEPROM_sd_config_txt.time_off_m;
      day_st[0] = EEPROM_sd_config_txt.day_st[0];
      day_st[1] = EEPROM_sd_config_txt.day_st[1];
      day_st[2] = EEPROM_sd_config_txt.day_st[2];
      day_st[3] = EEPROM_sd_config_txt.day_st[3];
      day_st[4] = EEPROM_sd_config_txt.day_st[4];
      day_st[5] = EEPROM_sd_config_txt.day_st[5];
      day_st[6] = EEPROM_sd_config_txt.day_st[6];
      lv_textarea_set_text(ui_TextArea1, String(time_on_h).c_str());
      lv_textarea_set_text(ui_TextArea2, String(time_on_m).c_str());
      lv_textarea_set_text(ui_TextArea3, String(time_off_h).c_str());
      lv_textarea_set_text(ui_TextArea4, String(time_off_m).c_str());
      lv_textarea_set_text(ui_TextArea5, String(EEPROM_sd_config_txt.pass).c_str());
      if (day_st[0])
         lv_obj_add_state(ui_Checkbox1, LV_STATE_CHECKED);
      else
         lv_obj_clear_state(ui_Checkbox1, LV_STATE_CHECKED);
      if (day_st[1])
         lv_obj_add_state(ui_Checkbox2, LV_STATE_CHECKED);
      else
         lv_obj_clear_state(ui_Checkbox2, LV_STATE_CHECKED);
      if (day_st[2])
         lv_obj_add_state(ui_Checkbox3, LV_STATE_CHECKED);
      else
         lv_obj_clear_state(ui_Checkbox3, LV_STATE_CHECKED);
      if (day_st[3])
         lv_obj_add_state(ui_Checkbox4, LV_STATE_CHECKED);
      else
         lv_obj_clear_state(ui_Checkbox4, LV_STATE_CHECKED);
      if (day_st[4])
         lv_obj_add_state(ui_Checkbox5, LV_STATE_CHECKED);
      else
         lv_obj_clear_state(ui_Checkbox5, LV_STATE_CHECKED);
      if (day_st[5])
         lv_obj_add_state(ui_Checkbox6, LV_STATE_CHECKED);
      else
         lv_obj_clear_state(ui_Checkbox6, LV_STATE_CHECKED);
      if (day_st[6])
         lv_obj_add_state(ui_Checkbox7, LV_STATE_CHECKED);
      else
         lv_obj_clear_state(ui_Checkbox7, LV_STATE_CHECKED);
      fan_mode = EEPROM_sd_config_txt.fan_mode;
      if (fan_mode)
      {
         lv_obj_set_style_bg_color(ui_led1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN);
         lv_obj_set_style_border_color(ui_led1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN);
         lv_obj_set_style_bg_color(ui_led2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN);
         lv_obj_set_style_border_color(ui_led2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN);
      }
      else
      {
         lv_obj_set_style_bg_color(ui_led2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN);
         lv_obj_set_style_border_color(ui_led2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN);
         lv_obj_set_style_bg_color(ui_led1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN);
         lv_obj_set_style_border_color(ui_led1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN);
      }
      time_mode = EEPROM_sd_config_txt.time_mode;
      if (time_mode)
      {
         lv_obj_add_state(ui_Switch2, LV_STATE_CHECKED);
         lv_obj_set_style_bg_color(ui_led3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN);
         lv_obj_set_style_border_color(ui_led3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN);
      }
      else
      {
         lv_obj_clear_state(ui_Switch2, LV_STATE_CHECKED);
         lv_obj_set_style_bg_color(ui_led3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN);
         lv_obj_set_style_border_color(ui_led3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN);
      }
      fan_ST_M = EEPROM_sd_config_txt.fan_ST_M;
      time_on_off_st = EEPROM_sd_config_txt.time_on_off_st;
      fan_out = EEPROM_sd_config_txt.fan_out;
      lv_slider_set_value(ui_Slider3, EEPROM_sd_config_txt.set_time_out, LV_ANIM_ON);
      lv_label_set_text(ui_Label13, String(EEPROM_sd_config_txt.set_time_out).c_str());
      // if (fan_ST_M)
      // {
      //    lv_obj_set_style_bg_color(ui_led3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN);
      //    lv_obj_set_style_border_color(ui_led3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN);
      // }
      // else
      // {
      //    lv_obj_set_style_bg_color(ui_led3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN);
      //    lv_obj_set_style_border_color(ui_led3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN);
      // }
   }
}
void Timeseting_p_ep(lv_event_t *e)
{
   time_on_h = String(lv_textarea_get_text(ui_TextArea1)).toInt();
   time_on_m = String(lv_textarea_get_text(ui_TextArea2)).toInt();
   time_off_h = String(lv_textarea_get_text(ui_TextArea3)).toInt();
   time_off_m = String(lv_textarea_get_text(ui_TextArea4)).toInt();
   int mon = lv_obj_has_state(ui_Checkbox1, LV_STATE_CHECKED);
   int tue = lv_obj_has_state(ui_Checkbox2, LV_STATE_CHECKED);
   int wed = lv_obj_has_state(ui_Checkbox3, LV_STATE_CHECKED);
   int thu = lv_obj_has_state(ui_Checkbox4, LV_STATE_CHECKED);
   int fri = lv_obj_has_state(ui_Checkbox5, LV_STATE_CHECKED);
   int sat = lv_obj_has_state(ui_Checkbox6, LV_STATE_CHECKED);
   int sun = lv_obj_has_state(ui_Checkbox7, LV_STATE_CHECKED);
   EEPROM_sd_config_txt.time_on_h = time_on_h;
   EEPROM_sd_config_txt.time_on_m = time_on_m;
   EEPROM_sd_config_txt.time_off_h = time_off_h;
   EEPROM_sd_config_txt.time_off_m = time_off_m;
   EEPROM_sd_config_txt.day_st[0] = mon;
   EEPROM_sd_config_txt.day_st[1] = tue;
   EEPROM_sd_config_txt.day_st[2] = wed;
   EEPROM_sd_config_txt.day_st[3] = thu;
   EEPROM_sd_config_txt.day_st[4] = fri;
   EEPROM_sd_config_txt.day_st[5] = sat;
   EEPROM_sd_config_txt.day_st[6] = sun;
   EEPROM_commit_st = 1;
   // EEPROM.commit();
   eeprom_read();
}

void M_limi_num_on(lv_event_t *e)
{
   int time_on_m = String(lv_textarea_get_text(ui_TextArea2)).toInt();
   if (time_on_m >= 60)
   {
      lv_textarea_set_text(ui_TextArea2, "59");
   }
}

void H_limi_num_on(lv_event_t *e)
{
   int time_on_h = String(lv_textarea_get_text(ui_TextArea1)).toInt();
   if (time_on_h >= 24)
   {
      lv_textarea_set_text(ui_TextArea1, "23");
   }
}

void H_limi_num_off(lv_event_t *e)
{
   int time_off_h = String(lv_textarea_get_text(ui_TextArea3)).toInt();
   if (time_off_h >= 24)
   {
      lv_textarea_set_text(ui_TextArea3, "23");
   }
}

void M_limi_num_off(lv_event_t *e)
{
   int time_off_m = String(lv_textarea_get_text(ui_TextArea4)).toInt();
   if (time_off_m >= 60)
   {
      lv_textarea_set_text(ui_TextArea4, "59");
   }
}

Ticker toggler;
Ticker timeupdate;
Ticker output_f;
bool isBlinking = false;
bool isBlinking_f = false;
void toggle()
{
   if (WiFi_Networks_ST == 0)
   {
      if (isBlinking)
      {
         lv_obj_set_style_bg_color(ui_led4, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN);
         lv_obj_set_style_border_color(ui_led4, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN);
         isBlinking = false;
      }
      else
      {
         lv_obj_set_style_bg_color(ui_led4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN);
         lv_obj_set_style_border_color(ui_led4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN);
         isBlinking = true;
      }
   }
   else
   {
      lv_obj_set_style_bg_color(ui_led4, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN);
      lv_obj_set_style_border_color(ui_led4, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN);
   }
   // EEPROM_sd_config_txt.filter_co = 2000;
   if (EEPROM_sd_config_txt.filter_co >= 2000)
   {
      if (isBlinking_f)
      {
         lv_obj_add_flag(ui_Image3, LV_OBJ_FLAG_HIDDEN);
         isBlinking_f = false;
      }
      else
      {
         isBlinking_f = true;
         lv_obj_clear_flag(ui_Image3, LV_OBJ_FLAG_HIDDEN);
      }
   }
   else
   {
      lv_obj_add_flag(ui_Image3, LV_OBJ_FLAG_HIDDEN);
   }
   // lv_obj_clear_flag(ui_Image7, LV_OBJ_FLAG_HIDDEN);

   // lv_obj_add_flag(ui_Image7, LV_OBJ_FLAG_HIDDEN);
   // PM2_5 = PM2_5 + 10;
   // if (PM2_5 > 1000)
   //    PM2_5 = 0;
   if (PM2_5 < 15)
   {
      lv_obj_set_style_bg_color(ui_led5, lv_color_make(0x45, 0x8C, 0xCF), LV_PART_MAIN); // 458CCF
   }
   else if (PM2_5 < 25)
   {
      lv_obj_set_style_bg_color(ui_led5, lv_color_make(0x48, 0x90, 0x4D), LV_PART_MAIN); // 48904D
   }
   else if (PM2_5 < 37.5)
   {
      lv_obj_set_style_bg_color(ui_led5, lv_color_make(0xFF, 0xA3, 0x00), LV_PART_MAIN); // FFA300
   }
   else if (PM2_5 < 75)
   {
      lv_obj_set_style_bg_color(ui_led5, lv_color_make(0xE8, 0x49, 0x19), LV_PART_MAIN); // E84919
   }
   else
   {
      lv_obj_set_style_bg_color(ui_led5, lv_color_make(0xFF, 0x00, 0x2C), LV_PART_MAIN); // FF002C
   }

   lv_label_set_text(ui_Label6, String(PM2_5).c_str());
   lv_label_set_text(ui_Label7, String(PM10).c_str());
   lv_label_set_text(ui_Label8, String(Temperature).c_str());
   lv_label_set_text(ui_Label9, String(Humidity).c_str());
}
void printLocalTime()
{

   if (!getLocalTime(&timeinfo))
   {
      Serial.println("Failed to obtain time");
      return;
   }
   char timeStringBuff[4];
   strftime(timeStringBuff, sizeof(timeStringBuff), "%A", &timeinfo);
   String day_str(timeStringBuff);
   char timeStringBuffm[4];
   strftime(timeStringBuffm, sizeof(timeStringBuffm), "%B", &timeinfo);
   String mon_str(timeStringBuffm);
   int day_num = timeinfo.tm_mday;
   int hour_num = timeinfo.tm_hour;
   int min_num = timeinfo.tm_min;
   int wday = timeinfo.tm_wday;
   Serial.println(wday);
}
void timeupdate_f()
{
   DateTime now;
   if (xSemaphoreTake(i2cMutex, portMAX_DELAY) == pdTRUE && i2cMutex != NULL)
   {
      PCF.toggle(3);
      now = rtc.now();
      xSemaphoreGive(i2cMutex);
   }
   // Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
   // Serial.print(" ");
   // Serial.print(now.day(), DEC);
   // Serial.print(" ");
   // Serial.print(monsOf[now.month() - 1]);
   // Serial.print(' ');
   // Serial.print(now.hour(), DEC);
   // Serial.print(':');
   // Serial.print(now.minute(), DEC);
   // Serial.println();

   String day_str = daysOfTheWeek[now.dayOfTheWeek()];
   String mon_str = monsOf[now.month() - 1];
   int day_num = now.day();    // timeinfo.tm_mday;
   hour_num = now.hour();      // timeinfo.tm_hour;
   int min_num = now.minute(); // timeinfo.tm_min;

   int wday = 0;
   if (now.dayOfTheWeek() == 0)
   {
      wday = now.dayOfTheWeek() + 6;
   }
   else
   {
      wday = now.dayOfTheWeek() - 1;
   }
   wday_st = day_st[wday];
   String text = day_str + " " + String(day_num) + " " + mon_str + " " + String(hour_num) + ":" + String(min_num);
   y_m_d_h_n = String(now.day()) + "/" + String(now.month()) + "/" + String(now.year()) + " " + String(hour_num) + ":" + String(min_num) + ":" + String(now.second());
   int min_num_s = min_num + (hour_num * 60);
   int time_on_s = time_on_m + (time_on_h * 60);
   int time_off_s = time_off_m + (time_off_h * 60);
   if (time_off_s - time_on_s < 0)
   {
      if (min_num_s > time_on_s || min_num_s < time_off_s)
      {
         time_on_off_st = 1;
         EEPROM_sd_config_txt.time_on_off_st = time_on_off_st;
         // EEPROM.write(95, time_on_off_st);
         EEPROM_commit_st = 1;
      }
      else
      {
         time_on_off_st = 0;
         EEPROM_sd_config_txt.time_on_off_st = time_on_off_st;
         // EEPROM.write(95, time_on_off_st);
         EEPROM_commit_st = 1;
      }
   }
   else
   {
      if (min_num_s > time_on_s && min_num_s < time_off_s)
      {
         time_on_off_st = 1;
         EEPROM_sd_config_txt.time_on_off_st = time_on_off_st;
         // EEPROM.write(95, time_on_off_st);
         EEPROM_commit_st = 1;
      }
      else
      {
         time_on_off_st = 0;
         EEPROM_sd_config_txt.time_on_off_st = time_on_off_st;
         // EEPROM.write(95, time_on_off_st);
         EEPROM_commit_st = 1;
      }
   }
   // if (hour_num == time_on_h && min_num == time_on_m && min_num_b != min_num)
   // {
   //    time_on_off_st = 1;
   //    EEPROM_sd_config_txt.time_on_off_st = time_on_off_st;
   //    // EEPROM.write(95, time_on_off_st);
   //    EEPROM_commit_st = 1;
   // }
   // if (hour_num == time_off_h && min_num == time_off_m && min_num_b != min_num)
   // {
   //    time_on_off_st = 0;
   //    EEPROM_sd_config_txt.time_on_off_st = time_on_off_st;
   //    EEPROM_commit_st = 1;
   // }
   if (hour_num == 3 && min_num == 30 && second_num_x < 30)
   {
      // if (WiFi_Networks_ST == 1)
      // {

      //    if (!getLocalTime(&timeinfo))
      //    {
      //       Serial.println("Failed to obtain time");
      //       configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
      //    }
      //    else
      //    {
      //       if (xSemaphoreTake(i2cMutex, portMAX_DELAY) == pdTRUE && i2cMutex != NULL)
      //       {
      //          rtc.adjust(DateTime(timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec));
      //          xSemaphoreGive(i2cMutex);
      //       }
      //    }

      ESP.restart();
      // }
   }
   second_num_x = now.second();
   min_num_b = min_num;
   wdtx++;
   if (wdtx > 3)
   {
      Serial.println("rts wdt");
      delay(1000);
      ESP.restart();
   }
   Serial.print("Free heap: ");
   Serial.print(ESP.getFreeHeap());
   Serial.print(" wdt: ");
   Serial.print(wdtx);
   Serial.print(" ");
   Serial.println(wday_st);
   lv_label_set_text(ui_Label3, text.c_str());
}
void set_mode(lv_event_t *e)
{
   if (EEPROM_sd_config_txt.fan_mode == 0)
   {
      fan_mode = 1;
      EEPROM_sd_config_txt.fan_mode = fan_mode;
      EEPROM_commit_st = 1;
      // EEPROM.commit();
      lv_obj_set_style_bg_color(ui_led1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN);
      lv_obj_set_style_border_color(ui_led1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN);
      lv_obj_set_style_bg_color(ui_led2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN);
      lv_obj_set_style_border_color(ui_led2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN);
   }
   else
   {
      fan_mode = 0;
      EEPROM_sd_config_txt.fan_mode = fan_mode;
      EEPROM_commit_st = 1;
      // EEPROM.commit();
      lv_obj_set_style_bg_color(ui_led2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN);
      lv_obj_set_style_border_color(ui_led2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN);
      lv_obj_set_style_bg_color(ui_led1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN);
      lv_obj_set_style_border_color(ui_led1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN);
   }
}
void SW_on_off_time(lv_event_t *e)
{

   time_mode = lv_obj_has_state(ui_Switch2, LV_STATE_CHECKED);
   EEPROM_sd_config_txt.time_mode = time_mode;
   EEPROM_commit_st = 1;
   // EEPROM.commit();
   if (time_mode)
   {
      lv_obj_set_style_bg_color(ui_led3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN);
      lv_obj_set_style_border_color(ui_led3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN);
   }
   else
   {
      lv_obj_set_style_bg_color(ui_led3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN);
      lv_obj_set_style_border_color(ui_led3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN);
   }
   Serial.println(time_mode);
}
int count_pl = 0;
void EEPROM_commit_f(void *pvParameters)
{

   for (;;)
   {

      if (xSemaphoreTake(i2cMutex, portMAX_DELAY) == pdTRUE && i2cMutex != NULL)
      {
         if (touch_touched())
         {
            touch_xxxx = touch_last_x;
            touch_yyyy = touch_last_y;
            touch_ssss = true;
         }
         else
         {
            touch_ssss = false;
         }
         xSemaphoreGive(i2cMutex);
      }
      delay(10);
   }
}
void Sensor_Read(void *pvParameters)
{
   Serial1.begin(9600, SERIAL_8N1, 17, 18);
   delay(500);
   // pms.activeMode();
   for (;;)
   {
      count_pl++;
      if (count_pl > 1000)
      {
         if (xSemaphoreTake(i2cMutex, portMAX_DELAY) == pdTRUE && i2cMutex != NULL)
         {
            if (PCF.readButton(5) == 0)
            {
               filter_reset = filter_reset + 1;
            }
            else
            {
               filter_reset = 0;
            }
            if (filter_reset > 10)
            {
               
               EEPROM_sd_config_txt.filter_co = 0;
               filter_reset = 0;
               Serial.println("reset =");
               EEPROM_commit_st = 1;
            }
            int Temperature_xx = sht31.readTemperature() - 1;
            if (Temperature_xx < 100)
            {
               Temperature = Temperature_xx;
               Humidity = sht31.readHumidity();
            }
            xSemaphoreGive(i2cMutex);
         }
         // Serial1.begin(9600, SERIAL_8N1, 18, 17);
         // delay(10);
         // if (pms.read(data_s))
         // {
         // PM2_5 = data_s.PM_AE_UG_2_5;
         // PM10 = data_s.PM_AE_UG_10_0;
         unsigned int pm1 = 0;
         unsigned int pm2_5 = 0;
         unsigned int pm10 = 0;
         int index = 0;
         char value;
         char previousValue;
         // if (Serial1.available())
         // {
         //    if (Serial1.peek() == 0x42)
         //    {
         //       byte buffer[32];
         //       Serial1.readBytes(buffer, 32);

         //       if (buffer[1] == 0x4D && buffer[0] == 0x42)
         //       {
         //          pm1 = buffer[4] * 256 + buffer[5];
         //          pm2_5 = buffer[12] * 256 + buffer[13];
         //          pm10 = buffer[14] * 256 + buffer[15];
         //          if (pm2_5 < 2000 && pm2_5 > 0)
         //             PM2_5 = pm2_5;
         //          if (pm10 < 2000 && pm10 > 0)
         //             PM10 = pm10;
         //       }
         //    }
         // }
         while (Serial1.available())
         {
            value = Serial1.read();
            // Serial.println(value,HEX);
            if ((index == 0 && value != 0x42) || (index == 1 && value != 0x4d))
            {
               break;
            }

            if (index == 4 || index == 6 || index == 8 || index == 10 || index == 12 || index == 14)
            {
               previousValue = value;
            }
            else if (index == 11)
            {
               pm1 = 256 * previousValue + value;
            }
            else if (index == 13)
            {
               pm2_5 = 256 * previousValue + value;
               if (pm2_5 < 2000 && pm2_5 > 0)
                  PM2_5 = pm2_5;
            }
            else if (index == 15)
            {
               pm10 = 256 * previousValue + value;
               if (pm10 < 2000 && pm10 > 0)
                  PM10 = pm10;
            }
            else if (index > 15)
            {
               break;
            }
            index++;
         }
         while (Serial1.available())
            Serial1.read();
         // }
         // Serial.println(pm2_5);
         count_pl = 0;
      }
      delay(1);
   }
}
// struct {
//    String ssid="CMMC_test";
//    String pass="CMMC_test";
//    String ID="ID000";
// } EEPROM_sd_config_txt;
void data_sd_save_f(void *pvParameters)
{
   pinMode(10, OUTPUT);
   File dataFile;
   File fileconfigw;
   File fileconfig;
   int sd_st = 0;
   if (!SD.begin(10))
   {
      Serial.println("Card failed, or not present");
      sd_st = 0;
   }
   else
   {
      sd_st = 1;
      Serial.println("card initialized.");
   }
   fileconfig = SD.open("/config.txt", FILE_READ);
   if (fileconfig)
   {
      // Read data into the struct
      fileconfig.read((uint8_t *)&EEPROM_sd_config_txt, sizeof(EEPROM_sd_config_txt));

      // Close the file
      fileconfig.close();

      if (EEPROM_sd_config_txt.set_time_out < 10)
         EEPROM_sd_config_txt.set_time_out = 10;

      // Print the data (optional)
      Serial.print("ssid: ");
      Serial.println(EEPROM_sd_config_txt.ssid);
      Serial.print("pass: ");
      Serial.println(EEPROM_sd_config_txt.pass);
      Serial.print("ID: ");
      Serial.println(EEPROM_sd_config_txt.ID);
      Serial.print("filter: ");
      Serial.println(EEPROM_sd_config_txt.filter_co);
   }
   else
   {
      Serial.println("Error opening file");
      if (EEPROM_sd_config_txt.set_time_out < 10)
         EEPROM_sd_config_txt.set_time_out = 10;
      fileconfigw = SD.open("/config.txt", FILE_WRITE);

      if (fileconfigw)
      {
         // Write data from the struct to the file
         fileconfigw.write((uint8_t *)&EEPROM_sd_config_txt, sizeof(EEPROM_sd_config_txt));

         // Close the file
         fileconfigw.close();

         Serial.println("Data written to SD card x");
      }
      else
      {
         Serial.println("Error opening file");
      }
   }
   for (;;)
   {
      if (hour_num != hour_num_b && sd_st == 1) //&& abs(hour_num-hour_num_b) == 1)
      {
         if (fan_out >= 1)
         {
            EEPROM_sd_config_txt.filter_co = EEPROM_sd_config_txt.filter_co + 1;
         }
         dataFile = SD.open("/Data_Logger.csv", FILE_APPEND);

         if (dataFile)
         {
            dataFile.println(y_m_d_h_n + "," + String(PM2_5) + "," + String(PM10) + "," + String(Temperature) + "," + String(Humidity) + "," + String(EEPROM_sd_config_txt.filter_co));
            dataFile.close();
            Serial.println("Data written to file.");
         }
         else
         {
            Serial.println("Error opening file.");
         }
         EEPROM_commit_st = 1;
      }
      else
      {
         if (EEPROM_commit_st == 1)
         {
            if (EEPROM_sd_config_txt.set_time_out < 10)
               EEPROM_sd_config_txt.set_time_out = 10;
            EEPROM_commit_st = 0;
            fileconfigw = SD.open("/config.txt", FILE_WRITE);
            if (fileconfigw)
            {
               fileconfigw.write((uint8_t *)&EEPROM_sd_config_txt, sizeof(EEPROM_sd_config_txt));
               fileconfigw.close();
               Serial.println("Data written to SD card");
            }
            else
            {
               EEPROM_commit_st == 1;
               Serial.println("Error opening file");
            }
         }
      }
      // if (SD.exists("/Data_Logger.csv"))
      // {
      //    Serial.println("Data_Logger.txt exists.");
      // }
      // else
      // {
      //    Serial.println("Data_Logger.txt doesn't exist.");
      // }
      // dataFile = SD.open("/Data_Logger.csv", FILE_APPEND);

      // if (dataFile)
      // {
      //    dataFile.println(y_m_d_h_n + "," + String(PM2_5) + "," + String(PM10) + "," + String(Temperature) + "," + String(Humidity));
      //    dataFile.close();
      //    Serial.println("Data written to file.");
      // }
      // else
      // {
      //    Serial.println("Error opening file.");
      // }
      // if (SD.exists("/Data_Logger.csv"))
      // {
      //    Serial.println("Data_Logger.txt exists.");
      // }
      // else
      // {
      //    Serial.println("Data_Logger.txt doesn't exist.");
      // }
      hour_num_b = hour_num;
      // Serial.println(y_m_d_h_n);
      delay(1000);
      touch_time_out = touch_time_out + 1;
      if (EEPROM_sd_config_txt.set_time_out < 10)
         EEPROM_sd_config_txt.set_time_out = 10;
      if (touch_time_out > EEPROM_sd_config_txt.set_time_out)
      {
         ledcWrite(0, 0);
      }
      else
      {
         ledcWrite(0, 255);
      }
   }
}
int fan_atoxxxxx(int pm = 0)
{
   if (pm > 37)
   {
      return 3;
   }
   else if (pm > 25)
   {
      return 2;
   }
   else if (pm > 1)
   {
      return 1;
   }
   else
   {
      return 0;
   }
}
void setup()
{
   Serial.begin(115200);
   Serial.print("MOSI: ");
   Serial.println(MOSI);
   Serial.print("MISO: ");
   Serial.println(MISO);
   Serial.print("SCK: ");
   Serial.println(SCK);
   Serial.print("SS: ");
   Serial.println(SS);
   // if (!EEPROM.begin(EEPROM_SIZE))
   // {
   //    Serial.println("failed to initialise EEPROM");
   //    delay(1000);
   //    ESP.restart();
   // }

   Serial.println("LVGL Benchmark Demo");

   // Init Display
   gfx->begin();
   gfx->fillScreen(BLACK);

   pinMode(TFT_BL, OUTPUT);
   ledcSetup(0, 1000, 8);
   ledcAttachPin(TFT_BL, 0);
   ledcWrite(0, 255);

   // digitalWrite(TFT_BL, HIGH);

   Wire.begin(TOUCH_GT911_SDA, TOUCH_GT911_SCL);
   touch_init();
   if (!rtc.begin())
   {
      Serial.println("Couldn't find RTC");
      Serial.flush();
   }
   if (!PCF.begin())
   {
      Serial.println("could not initialize...");
   }
   if (!PCF.isConnected())
   {
      Serial.println("=> not connected");
      // while (1)
      ;
   }
   // // if (rtc.lostPower())
   // // {
   // //    Serial.println("RTC lost power, let's set the time!");

   // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
   //    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
   // // }
   Serial.println("SHT31 test");
   if (!sht31.begin(0x44))
   { // Set to 0x45 for alternate i2c addr
      Serial.println("Couldn't find SHT31");
   }
   PCF.write(6, LOW);
   delay(200);
   PCF.write(6, HIGH);
   i2cMutex = xSemaphoreCreateMutex();
   xTaskCreatePinnedToCore(
       EEPROM_commit_f,
       "EEPROM_commit",
       10000,
       NULL,
       1,
       &EEPROM_commit,
       1);
   delay(250);
   xTaskCreatePinnedToCore(
       Sensor_Read,
       "Read_Sensor",
       10000,
       NULL,
       1,
       &Read_Sensor,
       1);
   delay(250);
   xTaskCreatePinnedToCore(
       data_sd_save_f,
       "data_sd_save",
       10000,
       NULL,
       1,
       &data_sd_save,
       1);
   delay(250);

   lv_init();

   screenWidth = gfx->width();
   screenHeight = gfx->height();
#ifdef ESP32
   disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * screenHeight / 4, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
#else
   disp_draw_buf = (lv_color_t *)malloc(sizeof(lv_color_t) * screenWidth * screenHeight / 4);
#endif
   if (!disp_draw_buf)
   {
      Serial.println("LVGL disp_draw_buf allocate failed!");
   }
   else
   {
      lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * screenHeight / 4);

      /* Initialize the display */
      lv_disp_drv_init(&disp_drv);
      /* Change the following line to your display resolution */
      disp_drv.hor_res = screenWidth;
      disp_drv.ver_res = screenHeight;
      disp_drv.flush_cb = my_disp_flush;
      disp_drv.draw_buf = &draw_buf;
      lv_disp_drv_register(&disp_drv);

      /* Initialize the (dummy) input device driver */
      static lv_indev_drv_t indev_drv;
      lv_indev_drv_init(&indev_drv);
      indev_drv.type = LV_INDEV_TYPE_POINTER;
      indev_drv.read_cb = my_touchpad_read;
      lv_indev_drv_register(&indev_drv);

      // lv_demo_benchmark();
      ui_init();

      Serial.println("Setup done");
   }
   last_ms = millis();

   String ssid_x = EEPROM_sd_config_txt.ssid;
   String pass_x = EEPROM_sd_config_txt.pass;
   Serial.println(ssid_x + "," + pass_x);
   WiFi.begin(ssid_x.c_str(), pass_x.c_str());
   eeprom_read();
   toggler.attach(0.5, toggle);
   // output_f.attach(1, timeupdate_f);
   timeupdate.attach(30, timeupdate_f);
   lv_label_set_text(ui_Ver, String(Ver).c_str());
   if (xSemaphoreTake(i2cMutex, portMAX_DELAY) == pdTRUE && i2cMutex != NULL)
   {
      if (fan_out == 1)
      {
         PCF.write(0, LOW);
         PCF.write(1, HIGH);
         PCF.write(2, HIGH);
      }
      else if (fan_out == 2)
      {
         PCF.write(0, HIGH);
         PCF.write(1, LOW);
         PCF.write(2, HIGH);
      }
      else if (fan_out == 3)
      {
         PCF.write(0, HIGH);
         PCF.write(1, HIGH);
         PCF.write(2, LOW);
      }
      else
      {
         PCF.write(0, HIGH);
         PCF.write(1, HIGH);
         PCF.write(2, HIGH);
      }
      xSemaphoreGive(i2cMutex);
   }
}

void loop()
{
   lv_timer_handler();
   if (WiFi.status() == WL_CONNECTED)
   {
      WiFi_Networks_ST = 1;
   }
   else
   {
      WiFi_Networks_ST = 0;
   }
   if (WiFi_Networks_ST_b == 0 && WiFi_Networks_ST == 1)
   {
      configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

      if (!getLocalTime(&timeinfo))
      {
         Serial.println("Failed to obtain time");
         configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
      }
      else
      {
         if (xSemaphoreTake(i2cMutex, portMAX_DELAY) == pdTRUE && i2cMutex != NULL)
         {
            rtc.adjust(DateTime(timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec));
            xSemaphoreGive(i2cMutex);
         }
         // Serial.print(timeinfo.tm_year + 1900);
         // Serial.print(" ");
         // Serial.print(timeinfo.tm_mday, DEC);
         // Serial.print(" ");
         // Serial.print(timeinfo.tm_mon + 1);
         // Serial.print(' ');
         // Serial.print(timeinfo.tm_hour, DEC);
         // Serial.print(':');
         // Serial.print(timeinfo.tm_min, DEC);
         // Serial.println();
         // delay(1000);
      }
      timeupdate_f();
      // printLocalTime();
   }
   WiFi_Networks_ST_b = WiFi_Networks_ST;
   if (time_mode == 1)
   {
      if (wday_st == 1)
      {
         if (time_on_off_st == 1)
         {
            if (fan_mode == 1)
            {
               fan_out = fan_atoxxxxx(PM2_5);
            }
            else
            {
               fan_out = fan_ST_M;
            }
         }
         else
         {
            fan_out = 0;
         }
      }
      else
      {
         fan_out = 0;
      }
   }
   else
   {
      if (fan_mode == 1)
      { // อโต้
         fan_out = fan_atoxxxxx(PM2_5);
      }
      else
      {
         fan_out = fan_ST_M;
      }
   }
   if (fan_out != fan_out_b)
   {
      EEPROM_sd_config_txt.fan_out = fan_out;
      EEPROM_commit_st = 1;
      if (xSemaphoreTake(i2cMutex, portMAX_DELAY) == pdTRUE && i2cMutex != NULL)
      {
         if (fan_out == 1)
         {
            PCF.write(0, LOW);
            PCF.write(1, HIGH);
            PCF.write(2, HIGH);
         }
         else if (fan_out == 2)
         {
            PCF.write(0, HIGH);
            PCF.write(1, LOW);
            PCF.write(2, HIGH);
         }
         else if (fan_out == 3)
         {
            PCF.write(0, HIGH);
            PCF.write(1, HIGH);
            PCF.write(2, LOW);
         }
         else
         {
            PCF.write(0, HIGH);
            PCF.write(1, HIGH);
            PCF.write(2, HIGH);
         }
         xSemaphoreGive(i2cMutex);
      }
      lv_bar_set_value(ui_Bar1, fan_out, LV_ANIM_ON);
   }
   fan_out_b = fan_out;

   delay(1);
}
