#include "buzzer_timer_interrupt.h"
#include "output.h"

extern BuzzerState buzzer_state;

void buzzer_timer_interrupt(void)
{
  switch (buzzer_state) {
    case BUZZER_OFF:
      return;
    case BUZZER_PLAYING:
      update_ball_sound();
  }
}
