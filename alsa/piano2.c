/*
S. Chand 2016
piano emulator for GNU/Linux
*/

#include <stdio.h>
#include <alsa/asoundlib.h>
#include <math.h>
#include <string.h>


#define BUFSIZE 32000
#define ACT_BUFSIZE BUFSIZE 
#define NOTESIZE 3

/* approximate frequencies of notes */
int f_c = 261;
int f_d = 293;
int f_e = 329;
int f_f = 349;
int f_g = 391;
int f_a = 440;
int f_b = 493;

/*parse_note: read a note and return frequency */
int parse_note(char *c)
{
    if (strcmp(c, "C") == 0)
        return f_c;
    else if (strcmp(c, "D") == 0)
        return f_d;
    else if (strcmp(c, "E") == 0)
        return f_e;
    else if (strcmp(c, "F") == 0)
        return f_f;
    else if (strcmp(c, "G") == 0)
        return f_g;
    else if (strcmp(c, "A") == 0)
        return f_a;
    else if (strcmp(c, "B") == 0)
        return f_b;

    return -1;
}



int main()
{ 
    static char *device = "default";
    int rv;
    int freq = 261;         /* roughly for middle C */

    int samp_rate = 44100;
    int dir;
    float buffer[ACT_BUFSIZE];

    char note[NOTESIZE];
    int i;
    int in_freq;

    snd_pcm_t *handle;
    snd_pcm_hw_params_t *params;
    snd_pcm_uframes_t frames = 16;

    rv = snd_pcm_open(&handle, device, SND_PCM_STREAM_PLAYBACK, 0);
    
    if (rv < 0) {
        fprintf(stderr, "error: could not open device. %s\n", 
                        snd_strerror(rv));
    }

    /* Mundane configurations for hw params.
       Chose to forego error checking.
    */

    snd_pcm_hw_params_malloc(&params);
    snd_pcm_hw_params_any(handle, params);

    snd_pcm_hw_params_set_access(handle, params,
                                 SND_PCM_ACCESS_RW_INTERLEAVED);

    snd_pcm_hw_params_set_format(handle, params, 
                                 SND_PCM_FORMAT_FLOAT);

    /* mono */
    snd_pcm_hw_params_set_channels(handle, params, 1);

    snd_pcm_hw_params_set_rate_near(handle, params, &samp_rate, &dir);

    snd_pcm_hw_params_set_period_size_near(handle, params, &frames, &dir);
    
    /* Now, prepare interface for use */
    if ((rv = snd_pcm_hw_params(handle, params)) < 0) {
        fprintf(stderr, "error: %s \n", snd_strerror(rv));
        exit(1);
    }

    snd_pcm_hw_params_free(params);

    /* Now, fill the buffer with the values and 
       write to the sound card's hardware buffer for
       actual playback.
    */
    
    printf("INIT NOTE: ");
    while (fgets(note, NOTESIZE-1, stdin) != NULL) {
        
        in_freq = parse_note(note);
        printf("\nOBT: %d\n", in_freq);
        if (in_freq != -1) {
            
            for (i = 0; i < BUFSIZE; i++) {
                
                buffer[i] = sin((2 *M_PI*in_freq)/samp_rate * i);
            }
            snd_pcm_writei(handle, buffer, ACT_BUFSIZE);
            snd_pcm_drain(handle);
            snd_pcm_prepare(handle);
        }
        printf("NOTE: ");
   }

    snd_pcm_close(handle);

    return 0;
}
