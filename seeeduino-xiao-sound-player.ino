#include "samples.h"

const int pin_pir_motion_sensor = 1;
const int pin_dac = DAC0;

const int dac_bits = 8;
const int rate = 16000;

const int play_count = 1;

const int sample_count = sizeof(samples) / sizeof(samples[0]);
// micros_compensation is used to compensate for execution time of micros() etc.
// the value was determined by comparing the original pitch vs. the output pitch
const int micros_compensation = 8;
// integer division is lossy, so let's multiply by 2 before dividing, (complicating the formula a bit)
const int sleep_micros_times_2 = (2 * 1000000 / rate) - (2 * micros_compensation);

unsigned long last_micros;
int remaining_plays = 0;
void setup() {
  analogWriteResolution(dac_bits);
  pinMode(pin_pir_motion_sensor, INPUT);
  last_micros = micros();
}

void sleep() {
  unsigned long now_micros = micros();
  unsigned long elapsed_micros = now_micros - last_micros;
  long remaining_sleep = sleep_micros_times_2 - elapsed_micros;
  if (remaining_sleep > 0)
    delayMicroseconds(remaining_sleep);
  last_micros = now_micros;
}

void loop() {
  if (remaining_plays == 0) {
    int moving = digitalRead(pin_pir_motion_sensor);
//    Serial.println(moving);
    if (moving)
      remaining_plays = play_count;
    else
      delay(1000);
  }
  else
  {
    remaining_plays--;

    for (int i = 0; i < sample_count; i++)
    {
      analogWrite(pin_dac, samples[i]);
      sleep();
    }
    if (remaining_plays == 0)
      delay(5000);
  }
}
