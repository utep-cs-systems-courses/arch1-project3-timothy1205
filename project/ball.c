#include <stdlib.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "ball.h"
#include "lcd.h"

#define BALL_SIZE 5

static Ball *balls;

void generate_balls()
{
  balls = calloc(BALL_COUNT, sizeof(Ball));
  unsigned short colors[] = { COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_PURPLE };

  // We need BALL_COUNT + 1 spaces, calculate size of each space
  unsigned short spacing = (screenWidth - (BALL_SIZE * BALL_COUNT)) / (BALL_COUNT + 1);
  for (char i = 0; i < BALL_COUNT; ++i) {
    balls[i].x = spacing * (i + 1) + BALL_SIZE * i;
    balls[i].y = (screenHeight / 2) - (BALL_SIZE / 2);

    balls[i].vel_x = 1 * (i + 1);
    balls[i].vel_y = 1 * (i + 1);

    balls[i].color = colors[i];
  }
}


static void pre_update()
{
  for (char i = 0; i < BALL_COUNT; ++i) {
    fillRectangle(balls[i].x, balls[i].y, BALL_SIZE, BALL_SIZE, LCD_BG);
  }
}

static void update_ball(Ball *ball)
{
  // Apply velocity
  ball->x += ball->vel_x;
  ball->y += ball->vel_y;

  /*
   * Wall collisions
   */
  if (ball->x + BALL_SIZE > screenWidth) {
    ball->x = screenWidth - BALL_SIZE;
    ball->vel_x *= -1; // Flip direction
  } else if (ball->x < 0) {
    ball->x = 0;
    ball->vel_x *= -1; // Flip direction
  }

  if (ball->y + BALL_SIZE > screenHeight) {
    ball->y = screenHeight - BALL_SIZE;
    ball->vel_y *= -1; // Flip direction
  } else if (ball->y < 0) {
    ball->y = 0;
    ball->vel_y *= -1; // Flip direction
  }
}

static void update_balls()
{
  for (char i = 0; i < BALL_COUNT; ++i) {
    update_ball(balls + i);
  }

}

static void post_update()
{
  for (char i = 0; i < BALL_COUNT; ++i) {
    fillRectangle(balls[i].x, balls[i].y, BALL_SIZE, BALL_SIZE, balls[i].color);
  }

}


void redraw_balls()
{
  pre_update(); // Remove old ball
  update_balls(); // Update position
  post_update(); // Draw at new position
}
