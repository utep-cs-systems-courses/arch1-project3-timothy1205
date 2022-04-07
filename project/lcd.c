#include <msp430.h>
#include "libTimer.h"
#include "input.h"
#include "output.h"
#include "toy.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "lcd.h"

//char redrawScreen = 1;
short redrawScreen = 1;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if (secCount >= 100) {		/* 10/sec */
    secCount = 0;
    redrawScreen = 1;
  }
}

void lcd_loop(void)
{
  if (redrawScreen) {
    redrawScreen = 0;
    clearScreen(COLOR_GREEN);
    static short xpos = 0;
    if (xpos++ > 100) xpos = 0;
    fillRectangle(xpos, 0, 50, 50, COLOR_WHITE);
  } else {
   // update_screen();
  }
}

void update_screen(void)
{
  clearScreen(COLOR_RED);
  fillRectangle(0, 0, 50, 50, COLOR_WHITE);
}
