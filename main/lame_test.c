#include "lame.h"
#include "lame_test.h"
#include <assert.h>


void lameTest()
{
 lame_global_flags *gfp;
 unsigned int sampleRate = 16000;
 int framesize = 0;

 /* Init lame flags.*/
 gfp = lame_init();
 if(!gfp) {
	 	   printf("Unable to initialize gfp object.\n");
	      } else {
	       printf("Able to initialize gfp object.\n");
	      }

 /* set other parameters.*/
 lame_set_VBR(gfp, vbr_default);
 lame_set_num_channels(gfp, 2);
 lame_set_in_samplerate(gfp, sampleRate);
 lame_set_quality(gfp, 7);  /* set for high speed and good quality. */
 lame_set_mode(gfp, 1);  /* audio is joint stereo */

 lame_set_out_samplerate(gfp, sampleRate);
 printf("Able to set a number of parameters too.\n");


 /* set more internal variables. check for failure.*/
 int initRet = lame_init_params(gfp);
 if(initRet < 0) {
   printf("Fail in setting internal parameters with code=%d\n",initRet);
 }

 framesize = lame_get_framesize(gfp);
 printf("Framesize = %d\n", framesize);
 assert(framesize <= 1152);




 lame_close(gfp);
 printf("Close\n");
}
