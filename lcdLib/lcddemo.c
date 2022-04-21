/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include <string.h>

#define TEXT_BAR_HEIGHT 30
static char msg[50];
static char msg2[] = "gooooodbye";
char s[5];
/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  /*
  clearScreen(COLOR_BLUE);

  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);

  fillRectangle(30,30, 60, 60, COLOR_ORANGE);
  */
  clearScreen(COLOR_PURPLE);
  
  strcpy(s, "hi");

  fillRectangle(0, 0, screenWidth, TEXT_BAR_HEIGHT, COLOR_WHITE);
  drawString8x12(0, TEXT_BAR_HEIGHT / 2 - 4, s, COLOR_BLACK, COLOR_WHITE);
  
  //strcpy(msg, msg2);
  //drawString5x7(20, 20, "hi", COLOR_BLACK, COLOR_YELLOW);
  //drawString8x12(20, 40, "hello", COLOR_BLACK, COLOR_YELLOW);
  //drawString11x16(20, 60, msg, COLOR_BLACK, COLOR_ORANGE);

  /*
  int length = 20;
  int fCol = 50, fRow = 50;

  // crossed triangle
  for (int a = 0; a < length; a++) {
    drawPixel(fCol + a, fRow + a, COLOR_BLUE);
    drawPixel(fCol + a, fRow, COLOR_PURPLE);
    drawPixel(fCol + length, fRow + a, COLOR_GREEN);

    if (a % 2 == 1) {
      for (int v = 0; v < a; v++) {
        drawPixel(fCol + a, fRow + v, COLOR_PINK);
        drawPixel(fCol + length - v, fRow + length - a, COLOR_RED);
      }
    }
  }

  // mirrored crossed triangle
  for (int a = 0; a < length; a++) {
    drawPixel(fCol + length + a, fRow, COLOR_BLUE);
    drawPixel(fCol + length, fRow - a, COLOR_PURPLE);
    drawPixel(fCol + length + a, fRow - length + a, COLOR_GREEN);

    //if (a % 2 == 1) {
    //  for (int v = 0; v < a; v++) {
    //    drawPixel(fCol + a, fRow + v, COLOR_PINK);
    //    drawPixel(fCol + length - v, fRow + length - a, COLOR_RED);
    //  }
    //}
  }


  int sCol = 50, sRow = 100, s = 0;
  // asterisk
  for (s = 0; s < length; s++) {
    drawPixel(sCol + s, sRow + s, COLOR_BLACK);
    drawPixel(sCol + (length / 2), sRow + s, COLOR_BLACK);
    drawPixel(sCol + s, sRow + (length / 2), COLOR_BLACK);
    drawPixel(sCol + length - s, sRow + s, COLOR_BLACK);
  }

  */
}
