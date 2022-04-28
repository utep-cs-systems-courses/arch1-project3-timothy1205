#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "lcd.h"
#include "output.h"
#include "ball.h"

short redrawScreen = 0;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if (secCount >= 8) { // about 60 fps
    secCount = 0;
    redrawScreen = 1;
  }
}

void game_loop()
{
  clearScreen(LCD_BG);

  generate_balls();

  while (1) {
    if (redrawScreen) {
      redrawScreen = 0;
      draw_screen();
    }

    led_red_off();
    or_sr(0x10);	/**< CPU OFF */
    led_red_on();
  }
}

void draw_screen()
{
  redraw_balls();
}
