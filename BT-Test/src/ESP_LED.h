#ifndef ESP_LED_h
#define ESP_LED_h

// LED constants
#define NUM_LEDS 3
#define LED0 15
#define LED1 16
#define LED2 17
#define NUM_SWS 4
#define SW0 4
#define SW1 5
#define SW2 6
#define SW3 7

// LED function declarations
void ledTask(int);
void setLED(int, int);
void setup_LED();
void proc_LED();

#endif