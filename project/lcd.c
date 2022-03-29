#include "libTimer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "lcd.h"

static char redrawScreen = 1;

void lcd_loop(void)
{
  clearScreen(COLOR_RED);
  while(1) {
    if (redrawScreen) {
      redrawScreen = 0;
      update_screen();
    }
  
    or_sr(0x10);
    }
}

void update_screen(void)
{
}
