#include <Arduino.h>
#define NUM_LEDS 3
#define LED0 15
#define LED1 16
#define LED2 17
#define NUM_SWS 4
#define SW0 4
#define SW1 5
#define SW2 6
#define SW3 7

// put function declarations here:
void ledTask(int);
void setLED(int, int);

// variable declarations
int ledState[NUM_LEDS];
int leds[NUM_LEDS] = {LED0, LED1, LED2};
int swStatePrev[NUM_SWS];
int swState[NUM_SWS];
int sws[] = {SW0, SW1, SW2, SW3};

void setup()
{
  Serial.begin(115200);

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  for (int i = 0; i < NUM_LEDS; i++)
  {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
    ledState[i] = LOW;
  }

  for (int i = 0; i < NUM_SWS; i++)
  {
    pinMode(sws[i], INPUT);
    swState[i] = digitalRead(sws[i]);
    swStatePrev[i] = LOW;
  }
}

void proc_LED()
{
  // Read all the switches first
  for (int i = 0; i < NUM_SWS; i++)
  {
    swState[i] = digitalRead(sws[i]);
  }

  // process the switch states
  for (int i = 0; i < NUM_SWS; i++)
  {
    if (swStatePrev[i] != swState[i] && swState[i] == 1)
    {
      ledTask(i);
    }

    swStatePrev[i] = swState[i];
  }

  delay(10);
}

void ledTask(int ledNum)
{
  if (ledNum >= NUM_LEDS)
  {
    return;
  }

  if (ledState[ledNum] == LOW)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      if (i != ledNum)
      {
        setLED(i, HIGH);
      }
    }

    delay(100);

    setLED(ledNum, HIGH);

    delay(100);

    for (int i = 0; i < NUM_LEDS; i++)
    {
      if (i != ledNum)
      {
        setLED(i, LOW);
      }
    }
  }
  else
  {
    setLED(ledNum, LOW);
  }
}

void setLED(int ledNum, int setLed)
{
  if (ledNum >= NUM_LEDS) {
    return;
  }

  digitalWrite(leds[ledNum], setLed);
  ledState[ledNum] = setLed;
}
