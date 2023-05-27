#include <math.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wren.h"
#include "fenster_audio.h"
#include "stb_vorbis.c"

#define STS_MONO_MIXER 1
#define STS_MIXER_IMPLEMENTATION
#include "sts_mixer_mono.h"

#include "audio.h"
#include "engine.h"
#include "log.h"
#include "utils_vec.h"

/*
** Global audio state
**
** You shouldn't have more than one audio context or
** you're gonna have a bad time
*/
struct fenster_audio audio_device;

/*
** Mixer
** I hate these globals, I should fix these libraries
*/
sts_mixer_t mixer;

/*
** Audio subsystem
*/

/*
** Audio thread worker
*/
// Thread for audio device
void *audio_thread(void *arg) {
    struct pe_audio *fa = (struct pe_audio *)arg;
    for (;;) {
        sts_mixer_mix_audio(&mixer, fa->audio_buffer, FENSTER_AUDIO_BUFSZ);
        fenster_audio_write(&audio_device, fa->audio_buffer, FENSTER_AUDIO_BUFSZ);
    }
    return NULL;
}

/*
** Load sample to memory
*/
void load_sample(sts_mixer_sample_t *sample, const char *filename) {
    int error = 0;
    stb_vorbis_alloc *sound_alloc = calloc(1, sizeof(stb_vorbis_alloc));
    stb_vorbis *vorbis =
        stb_vorbis_open_filename(filename, &error, sound_alloc);

    if (vorbis == NULL || error != VORBIS__no_error) {
        LOG_ERROR("Could not load sound file: %s\n", filename);
        return;
    }

    stb_vorbis_info info = stb_vorbis_get_info(vorbis);
    size_t size = info.channels * stb_vorbis_stream_length_in_samples(vorbis) *
                  sizeof(float);

    sample->frequency = info.sample_rate;
    sample->audio_format = STS_MIXER_SAMPLE_FORMAT_FLOAT;
    sample->length = vorbis->total_samples;
    sample->data = calloc(size, sizeof(float));
    CHECK_ALLOC(sample->data);

    // Print info
    LOG_DEBUG(" ** Filename: %s\n", filename);
    LOG_DEBUG(" -> Channels: %d\n", info.channels);
    LOG_DEBUG(" -> Sample rate: %d\n", info.sample_rate);
    LOG_DEBUG(" -> Total samples: %d\n",
              stb_vorbis_stream_length_in_samples(vorbis));
    LOG_DEBUG(" -> Total duration: %f\n",
              stb_vorbis_stream_length_in_seconds(vorbis));
    LOG_DEBUG("-> Memory required: %ld\n", size);

    LOG_DEBUG(" -> Loading samples...\n");
    stb_vorbis_get_samples_float_interleaved(
        vorbis, info.channels, (float *)sample->data, vorbis->total_samples);
    LOG_DEBUG(" -> Samples loaded.\n");
    stb_vorbis_close(vorbis);
}

/*
** Wren audio loading
*/
void pe_audio_load_sample(WrenVM *vm) {}

/*
** Start audio engine
*/
int pe_audio_start(struct pe_audio *fa) {
    LOG_DEBUG(" * Starting audio subsystem...\n");

    if (fenster_audio_open(&audio_device) < 0) {
        LOG_ERROR("Could not open audio device\n");
        return 1;
    }

    if (fenster_audio_available(&audio_device) < 0) {
        LOG_ERROR("Audio device not available.");
        return 1;
    }

    LOG_DEBUG(" -> Audio device opened.\n");
    sts_mixer_init(&mixer, FENSTER_SAMPLE_RATE,
                   STS_MIXER_SAMPLE_FORMAT_FLOAT);
    LOG_DEBUG(" -> Mixer initialized.\n");
    LOG_DEBUG("Audio subsystem started. Jolly good!\n");

    // Start audio thread
    if (pthread_create(&fa->audio_thread_id, NULL, audio_thread, fa) != 0) {
        LOG_ERROR("Could not create audio thread.\n");
        return 1;
    }

    return 0;
}

/*
** Kill audio engine
*/
void pe_audio_destroy(struct pe_audio *fa) {
    LOG_DEBUG(" * Destroying audio subsystem...\n");
    sts_mixer_shutdown(&mixer);
    fenster_audio_close(&audio_device);
    if (pthread_cancel(fa->audio_thread_id) != 0) {
        LOG_ERROR("Could not cancel audio thread.\n");
    }
    LOG_DEBUG("Audio subsystem destroyed.\n");
}

/*
** Expose audio functions to Wren
*/
void pe_audio_register_functions(struct pe_engine_state *engine_state) {}
