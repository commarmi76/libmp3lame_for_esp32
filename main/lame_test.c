#include "lame.h"
#include "lame_test.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include <assert.h>
#include <esp_types.h>
#include <stdio.h>
#include "rom/ets_sys.h"
#include "esp_heap_alloc_caps.h"
#include <stdlib.h>
#include <string.h>

extern const uint8_t Sample16kHz_raw_start[] asm("_binary_Sample16kHz_raw_start");
extern const uint8_t Sample16kHz_raw_end[]   asm("_binary_Sample16kHz_raw_end");

void lameTest()
{
 lame_t lame;
 unsigned int sampleRate = 16000;
 short int *pcm_samples;
 int framesize = 0;
 int num_samples_encoded = 0;
 size_t free8start, free32start;
 const int nsamples=1152;
 unsigned char *mp3buf;
 const int mp3buf_size=2000;

 free8start=xPortGetFreeHeapSizeCaps(MALLOC_CAP_8BIT);
 free32start=xPortGetFreeHeapSizeCaps(MALLOC_CAP_32BIT);
 printf("pre lame_init() free mem8bit: %d mem32bit: %d\n",free8start,free32start);

 mp3buf=malloc(mp3buf_size);

 /* Init lame flags.*/
 lame = lame_init();

 free8start=xPortGetFreeHeapSizeCaps(MALLOC_CAP_8BIT);
 free32start=xPortGetFreeHeapSizeCaps(MALLOC_CAP_32BIT);
 printf("post lame_init() free mem8bit: %d mem32bit: %d\n",free8start,free32start);

 if(!lame) {
	 	   printf("Unable to initialize lame object.\n");
	      } else {
	       printf("Able to initialize lame object.\n");
	      }

 /* set other parameters.*/
 lame_set_VBR(lame, vbr_default);
 lame_set_num_channels(lame, 2);
 lame_set_in_samplerate(lame, sampleRate);
 lame_set_quality(lame, 7);  /* set for high speed and good quality. */
 lame_set_mode(lame, JOINT_STEREO);  /* audio is joint stereo */

// lame_set_out_samplerate(lame, sampleRate);
 printf("Able to set a number of parameters too.\n");


 /* set more internal variables. check for failure.*/
 int initRet = lame_init_params(lame);
 if(initRet < 0) printf("Fail in setting internal parameters with code=%d\n",initRet);
 else printf("OK setting internal parameters\n");


 free8start=xPortGetFreeHeapSizeCaps(MALLOC_CAP_8BIT);
 printf("post lame_init_params() free mem: %d\n",free8start);

// lame_print_config(lame);
// lame_print_internals(lame);

 framesize = lame_get_framesize(lame);
 printf("Framesize = %d\n", framesize);
// assert(framesize <= 1152);

/*
 printf("Sample16kHz.raw start: %p", Sample16kHz_raw_start);
 printf(" end: %p", Sample16kHz_raw_end);
 printf(" with size: %d\n", Sample16kHz_raw_end-Sample16kHz_raw_start);
*/

 pcm_samples = (short int *)Sample16kHz_raw_start;

 for (int j=0;j<10;j++)
 {
	 printf("\n=============== lame_encode_buffer_interleaved================ \n");

 /* encode samples. */

	  num_samples_encoded = lame_encode_buffer_interleaved(lame, pcm_samples, nsamples, mp3buf, mp3buf_size);

     printf("number of samples encoded = %d\n", num_samples_encoded);

     /* check for value returned.*/
     if(num_samples_encoded > 1) {
       printf("It seems the conversion was successful.\n");
     } else if(num_samples_encoded == -1) {
       printf("mp3buf was too small\n");
       return ;
     } else if(num_samples_encoded == -2) {
       printf("There was a malloc problem.\n");
       return ;
     } else if(num_samples_encoded == -3) {
       printf("lame_init_params() not called.\n");
       return ;
     } else if(num_samples_encoded == -4) {
       printf("Psycho acoustic problems.\n");
       return ;
     } else if(num_samples_encoded == -11) {
       printf("McM test\n");
       return ;
     } else {
       printf("The conversion was not successful.\n");
       return ;
     }


     printf("Contents of mp3buffer = ");
     for(int i = 0; i < num_samples_encoded; i++) {
       printf("%d ", mp3buf[i]);
     }

    pcm_samples += (nsamples*2);

 }


// =========================================================


 lame_close(lame);
 printf("\nClose\n");

 while (1) vTaskDelay(500 / portTICK_RATE_MS);

 return;
}
