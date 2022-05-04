#include "cajon_guitar_8bit_16k_mono.h"

int dac_bits = 8;
int dac_out = DAC0;
int sleep_val = 48; // TODO: determine sleep time dynamically using micros()
int array_len = sizeof(cajon_guitar) / sizeof(cajon_guitar[0]);

void setup() {
  analogWriteResolution(dac_bits);
}

void loop() {
  for (int i = 0; i < array_len; i++)
  {
    analogWrite(dac_out, cajon_guitar[i]);
    delayMicroseconds(sleep_val);
  }
}
