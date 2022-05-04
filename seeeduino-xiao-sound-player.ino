#include "samples.h"

const int pin_ir_recv = 2;
//const int pin_ir_send = 3;

const int dac_bits = 8;
const int rate = 16000;
const int dac_out = DAC0;

const int play_count = 1;

const int sample_count = sizeof(samples) / sizeof(samples[0]);
// micros_compensation is used to compensate for execution time of micros() etc.
// the value was determined by comparing the original pitch vs. the output pitch
const int micros_compensation = 4;
// integer division is lossy, so let's multiply by 2 before dividing, (complicating the formula a bit)
const int sleep_micros_times_2 = (2 * 1000000 / rate) - (2 * micros_compensation);

unsigned long last_micros;
int remaining_plays = 0;
void setup() {
  analogWriteResolution(dac_bits);
  pinMode(pin_ir_recv, INPUT);
//  pinMode(pin_ir_send, OUTPUT);
//  digitalWrite(pin_ir_send, HIGH);
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

bool is_receiving_ir()
{
  return digitalRead(pin_ir_recv) == LOW;
}

void loop() {
  if (remaining_plays == 0) {
      int value = digitalRead(pin_ir_recv);
      if (value == 0)
        remaining_plays = play_count;
      else
        delay(1);
  }
  else
  {
    remaining_plays--;

    for (int i = 0; i < sample_count; i++)
    {
      analogWrite(dac_out, samples[i]);
      sleep();
    }
  }
}

//void loop() {
//  if (is_receiving_ir())
//  {
//    int last_ir_receival = 0;
//    for (int i = 0; i < sample_count; i++)
//    {
//      if (is_receiving_ir())
//        last_ir_receival = i;
//      else if (i - last_ir_receival > rate)
//        break;
//      analogWrite(dac_out, samples[i]);
//      sleep();
//    }
//  }
//  else
//  {
//    delay(1);
//  }
//}
