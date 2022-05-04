# Playi sound on the Seeeduino XIAO

This simple example plays 8 bit / 16k / mono sound sample in a loop on a Seeeduino XIAO.

The Seeeduino XIAO has
- one 10-bit DAC on pin 0 we will use to output sound to a speaker
- 256K flash memory we use to store sound data

I have attached a [Grove speaker](https://wiki.seeedstudio.com/Grove-Speaker/) to the Seeeduino XIAO:
- red cable to 5V
- black cable to GND
- yellow cable to DAC

# Convert WAV file to 8 bit, 16k, mono sample.h file
```
sox sound.wav -c1 -r16000 -tdat - \
| tail -n+3 \
| awk '
  BEGIN { printf "const PROGMEM byte samples[] = {\n" }
  { printf "  %.0f,\n", ($2+1)*128}
  END { printf "};\n"}' \
> samples.h
```
