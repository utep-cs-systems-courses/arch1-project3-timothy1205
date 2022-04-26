#ifndef output_included
#define output_included

#define LED_RED BIT6               // P1.6
#define LEDS (LED_RED)

typedef enum BuzzerState{ BUZZER_PLAYING, BUZZER_OFF } BuzzerState;

void buzzer_init(void);
void buzzer_set_period(short cycles);
void buzzer_stop(void);
void buzzer_timer_interrupt(void);

void led_init(void);
void led_red_on(void);
void led_red_off(void);

#endif
