#ifndef BALL_INCLUDED
#define BALL_INCLUDED

#define BALL_COUNT 4

typedef struct ball_struct {
  short x, y;
  short vel_x, vel_y;
  unsigned short color;
} Ball;

typedef enum ball_state_enum { BALL_NORMAL, BALL_CONVERGE } BallState;

void generate_balls();
void redraw_balls();

#endif
