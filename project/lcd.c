#include <msp430.h>
#include "libTimer.h"
#include "input.h"
#include "output.h"
#include "toy.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "lcd.h"

#define TEXT_BAR_HEIGHT 30

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
    
    update_screen();
  }
}

void update_screen(void)
{
  fillRectangle(0, 0, screenWidth, TEXT_BAR_HEIGHT, COLOR_WHITE);
}
