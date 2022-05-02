#ifndef BALL_INCLUDED
#define BALL_INCLUDED

#define BALL_COUNT 4

typedef struct ball_struct {
  short x, y;
  short vel_x, vel_y;
  unsigned short color;
} Ball;

typedef enum ball_state_enum { BALLS_WAITING, BALLS_NORMAL, BALLS_CONVERGE } BallState;

void generate_balls();
void redraw_balls();

void balls_start();
void balls_converge(u_char ball_index);
void balls_resume();

void balls_handle_interrupt();

#endif
