# libmp3lame_for_esp32
Experiments to port lame mp3 encoder to esp32

Original sources by the authors of LAME: http://www.sourceforge.net/projects/lame


First benchmark:
Encode Sample16kHz.raw (little-endian) data, 16 bit, stereo 16000 Hz

1. Without CFLAGS:
7925057 microseconds

2. With CFLAGS += -Wno-unused-function -DHAVE_EXPAT_CONFIG_H -O3 -ffast-math
7885191 microseconds

3. With CFLAGS (see above) and TAKEHIRO_IEEE754_HACK
8468706 microseconds

So, the best option is 1,26 realtime. 

TODO:
- Encode something infinite to check memory leaks
- Profile to find the heaviest parts
- Investigate esp32 dsp features: Vectra LX DSP Engine, MAC16
- Streaming over tcp and http


=================================================================================
Using the LAME encoding engine (or other mp3 encoding technology) in your software 
may require a patent license in some countries.

As LAME may contain software for which some companies may claim software
patents, if you are in a location where software patents are recognized, it is
suggested that you seek legal advice before deploying and/or redistributing
LAME.

In particular, it is suggested to visit

    http://www.mp3licensing.com/

if it applies to your jurisdiction.
