#include <msp430.h>
#include <string.h>
#include "libTimer.h"
#include "input.h"
#include "output.h"
#include "toy.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "lcd.h"

extern char* msg_buffer;
extern BuzzerState buzzer_state;

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

static char once = 0;
void update_screen(void)
{
  if (buzzer_state == BUZZER_PLAYING && !once) {
    // Initial draw
    fillRectangle(0, 0, 10, 30, COLOR_WHITE);
    drawString8x12(0, 11, s, COLOR_BLACK, COLOR_RED);
    once = 1;
  }
}
