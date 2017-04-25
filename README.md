# libmp3lame_for_esp32
Experiments to port lame mp3 encoder to esp32

Original sources by the authors of LAME: http://www.sourceforge.net/projects/lame

=================================================================================
First benchmark:
Encode Sample16kHz.raw (little-endian) data, 16 bit, stereo 16000 Hz 10 seconds

1. Without CFLAGS:
7925057 microseconds

2. With CFLAGS += -O3 -ffast-math:
7885191 microseconds

3. With CFLAGS (see above) and TAKEHIRO_IEEE754_HACK:
8468706 microseconds

4. With CFLAGS and release mode:
7220642 microseconds


So, the best option is (4): 1,38x realtime. 

=================================================================================
Encode the same file for more than an hour:

LOOP: free mem8bit: 11720 mem32bit: 19992 frames encoded: 139 bytes:99084

...

LOOP: free mem8bit: 11720 mem32bit: 19992 frames encoded: 88543 bytes:63669828

Isn't such a exhaustive test but enough for now.

=================================================================================
TODO:
- Encode something infinite to check memory leaks (partially done)
- Investigate why CONFIG_ENABLE_MEMORY_DEBUG=y crashes the system
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
