/*******************************************************************************
 * Touch libraries:
 * FT6X36: https://github.com/strange-v/FT6X36.git
 * GT911: https://github.com/TAMCTec/gt911-arduino.git
 * XPT2046: https://github.com/PaulStoffregen/XPT2046_Touchscreen.git
 ******************************************************************************/

/* uncomment for FT6X36 */
// #define TOUCH_FT6X36
// #define TOUCH_FT6X36_SCL 19
// #define TOUCH_FT6X36_SDA 18
// #define TOUCH_FT6X36_INT -1
// #define TOUCH_SWAP_XY
// #define TOUCH_MAP_X1 480
// #define TOUCH_MAP_X2 0
// #define TOUCH_MAP_Y1 0
// #define TOUCH_MAP_Y2 320

/* uncomment for GT911 */
#define TOUCH_GT911
#define TOUCH_GT911_SCL 20
#define TOUCH_GT911_SDA 19
#define TOUCH_GT911_INT -1
#define TOUCH_GT911_RST 38
#define TOUCH_GT911_ROTATION ROTATION_NORMAL
#define TOUCH_MAP_X1 479
#define TOUCH_MAP_X2 0
#define TOUCH_MAP_Y1 272
#define TOUCH_MAP_Y2 0

/* uncomment for XPT2046 */
// #define TOUCH_XPT2046
// #define TOUCH_XPT2046_SCK 12
// #define TOUCH_XPT2046_MISO 13
// #define TOUCH_XPT2046_MOSI 11
// #define TOUCH_XPT2046_CS 10
// #define TOUCH_XPT2046_INT 18
// #define TOUCH_XPT2046_ROTATION 0
// #define TOUCH_MAP_X1 4000
// #define TOUCH_MAP_X2 100
// #define TOUCH_MAP_Y1 100
// #define TOUCH_MAP_Y2 4000

int touch_last_x = 0, touch_last_y = 0;
int touch_last_x_b = 0, touch_last_y_b = 0;
#include <Wire.h>
#include "TAMC_GT911.h"
TAMC_GT911 ts = TAMC_GT911(TOUCH_GT911_SDA, TOUCH_GT911_SCL, TOUCH_GT911_INT, TOUCH_GT911_RST, max(TOUCH_MAP_X1, TOUCH_MAP_X2), max(TOUCH_MAP_Y1, TOUCH_MAP_Y2));

void touch_init(uint8_t add = 0x5D)
{

  Wire.begin(TOUCH_GT911_SDA, TOUCH_GT911_SCL);
  ts.begin(add);
  ts.setRotation(TOUCH_GT911_ROTATION);
}

bool touch_has_signal()
{
  return true;
}

bool touch_touched()
{
  //   ts.read();
  // if (ts.isTouched){
  //     if(ts.points[0].size>65){
  //     Serial.print("  x: ");Serial.print(ts.points[0].x);
  //     Serial.print("  y: ");Serial.print(ts.points[0].y);
  //     Serial.println(' ');
  // }

  // }
  ts.read();
  if (ts.isTouched)
  {
    // #if defined(TOUCH_SWAP_XY)
    // touch_last_x = map(ts.points[0].y, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, gfx->width() - 1);
    // touch_last_y = map(ts.points[0].x, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, gfx->height() - 1);
    // #else
    if (ts.points[0].size > 35)
    {
      touch_last_x_b = touch_last_x;
      touch_last_y_b = touch_last_y;
      // touch_last_x = (map(ts.points[0].x, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, gfx->width() - 1) + touch_last_x_b) / 2;
      // touch_last_y = (map(ts.points[0].y, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, gfx->height() - 1) + touch_last_y_b) / 2;
      touch_last_x = map(ts.points[0].x, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, gfx->width() - 1);
      touch_last_y = map(ts.points[0].y, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, gfx->height() - 1);
      // #endif
      return true;
    }
    return false;
  }
  else
  {
    return false;
  }
}

bool touch_released()
{
  return true;
}