# Playing sound on the Seeeduino XIAO

This simple example plays 8 bit / 16k / mono sound on a Seeeduino XIAO.

The Seeeduino XIAO has
- one 10-bit DAC on pin 0 we will use to output sound to a speaker
- 256K flash memory we use to store sound data

I have attached a [Grove speaker](https://wiki.seeedstudio.com/Grove-Speaker/) to the Seeeduino XIAO:
- red cable to 5V
- black cable to GND
- yellow cable to DAC

I converted a recording I made using audacity and sox to a 8 bit 16k mono .dat file and used awk to convert the dat file to the cajon_guitar....h file.
