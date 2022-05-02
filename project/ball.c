#include <stdlib.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "ball.h"
#include "lcd.h"
#include "output.h"
#include "input.h"

#define BALL_SIZE 5

extern int switches;

static Ball *balls;
static BallState ball_state = BALLS_WAITING; // start paused
static u_char ball_converge_index = 0;

void generate_balls()
{
  balls = calloc(BALL_COUNT, sizeof(Ball));
  unsigned short colors[] = { COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_PURPLE };

  // We need BALL_COUNT + 1 spaces, calculate size of each space
  unsigned short spacing = (screenWidth - (BALL_SIZE * BALL_COUNT)) / (BALL_COUNT + 1);
  for (char i = 0; i < BALL_COUNT; ++i) {
    balls[i].x = spacing * (i + 1) + BALL_SIZE * i;
    balls[i].y = (screenHeight / 2) - (BALL_SIZE / 2);

    balls[i].color = colors[i];
  }
}


static void pre_update()
{
  for (char i = 0; i < BALL_COUNT; ++i) {
    fillRectangle(balls[i].x, balls[i].y, BALL_SIZE, BALL_SIZE, LCD_BG);
  }
}

static void get_converge_offset(Ball *converger, Ball *convergee, short *x, short *y)
{
  if (converger->x < convergee->x)
    *x = 1;
  else if (converger->x = convergee->x)
    *x = 0;
  else
    *x = -1;

  if (converger->y < convergee->y)
    *y = 1;
  else if (converger->y = convergee->y)
    *y = 0;
  else
    *y = -1;
}

static void update_ball(Ball *ball)
{
  if (ball_state == BALLS_CONVERGE) {
    if (ball == balls + ball_converge_index) {
      // Can't converge on self
      return;
    }

    short offset_x = 0, offset_y = 0;
    get_converge_offset(ball, balls + ball_converge_index, &offset_x, &offset_y);
    ball->x += offset_x;
    ball->y += offset_y;
  } else {
    // Apply velocity
    ball->x += ball->vel_x;
    ball->y += ball->vel_y;

    /*
     * Wall collisions
     */
    if (ball->x + BALL_SIZE > screenWidth) {
      ball->x = screenWidth - BALL_SIZE;
      ball->vel_x *= -1; // Flip direction
      start_bounce_sound();
    } else if (ball->x < 0) {
      ball->x = 0;
      ball->vel_x *= -1; // Flip direction
      start_bounce_sound();
    }

    if (ball->y + BALL_SIZE > screenHeight) {
      ball->y = screenHeight - BALL_SIZE;
      ball->vel_y *= -1; // Flip direction
      start_bounce_sound();
    } else if (ball->y < 0) {
      ball->y = 0;
      ball->vel_y *= -1; // Flip direction
      start_bounce_sound();
    }
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



void balls_start()
{
  ball_state = BALLS_NORMAL;

  // Set initial velocities
  for (char i = 0; i < BALL_COUNT; ++i) {
    balls[i].vel_x = 1 * (i + 1);
    balls[i].vel_y = 1 * (i + 1);
  }
}

void balls_converge(u_char ball_index)
{
  ball_state = BALLS_CONVERGE;
  ball_converge_index = ball_index;
}

void balls_resume()
{
  ball_state = BALLS_NORMAL;
}


void balls_handle_interrupt()
{
  if (ball_state == BALLS_WAITING) {
    // Start for any switch
    balls_start();
  }
  
  if (ball_state == BALLS_CONVERGE) {
    // Check for no switches pressed
    if (switches == 0)
      balls_resume();
  } else {
      if (switches & SW1)
        balls_converge(0);
      else if (switches & SW2)
        balls_converge(1);
      else if (switches & SW3)
        balls_converge(2);
      else if (switches & SW4)
        balls_converge(3);
  }
}
