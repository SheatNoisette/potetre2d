#include <math.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "audio.h"
#include "engine.h"
#include "log.h"
#include "utils_vec.h"
#include "utils.h"

#include "wren.h"
#include "stb_vorbis.c"

#define FENSTER_AUDIO_BUFSZ (AUDIO_BUFFER_SIZE * 2)
#include "fenster_audio.h"

#define STS_MONO_MIXER 1
#define STS_MIXER_IMPLEMENTATION
#define STS_MIXER_VOICES 64
#include "sts_mixer_mono.h"

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
        sts_mixer_mix_audio(&mixer, fa->audio_buffer, AUDIO_BUFFER_SIZE);
        fenster_audio_write(&audio_device, fa->audio_buffer, AUDIO_BUFFER_SIZE);
    }
    return NULL;
}

/*
** Load sample to memory
*/
static int load_sample(sts_mixer_sample_t *sample, const char *filename) {
    int error = 0;
    stb_vorbis_alloc *sound_alloc = calloc(1, sizeof(stb_vorbis_alloc));
    stb_vorbis *vorbis =
        stb_vorbis_open_filename(filename, &error, sound_alloc);

    if (vorbis == NULL || error != VORBIS__no_error) {
        LOG_ERROR("Could not load sound file: %s\n", filename);
        return 1;
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

    return 0;
}

/*
** Wren audio loading
*/
void pe_audio_load_sample(WrenVM *vm) {
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));
    const char *filename = wrenGetSlotString(vm, 1);

    // Load sample into memory
    sts_mixer_sample_t *sample = calloc(1, sizeof(sts_mixer_sample_t));
    CHECK_ALLOC(sample);

    // Call vorbis loader
    if (load_sample(sample, filename) != 0) {
        LOG_ERROR("Error while loading %s!\n", filename);
        wrenSetSlotDouble(vm, 0, -1.);
        return;
    }

    // Add sample to vector
    size_t id = pe_vector_push(engine->audio->samples, sample);
    wrenSetSlotDouble(vm, 0, id);
}

/*
** Play sound
*/
void pe_audio_play(WrenVM *vm) {
    struct pe_engine_state *engine =
        ((struct pe_engine_state *)wrenGetUserData(vm));
    size_t id = wrenGetSlotDouble(vm, 1);
    float volume = wrenGetSlotDouble(vm, 2);
    float pitch = wrenGetSlotDouble(vm, 3);
    float pan = wrenGetSlotDouble(vm, 4);

    // Get sample
    sts_mixer_sample_t *sample = pe_vector_get(engine->audio->samples, id);
    if (sample == NULL) {
        LOG_ERROR("Could not find sample with id %ld\n", id);
        return;
    }

    // Play sample
    sts_mixer_play_sample(&mixer, sample, volume, pitch, pan);
}

/*
** Start audio engine
*/
int pe_audio_start(struct pe_audio *fa) {
    LOG_DEBUG(" * Starting audio subsystem...\n");

    if (fenster_audio_open(&audio_device) < 0) {
        LOG_ERROR("Could not open audio device\n");
        return 1;
    }
    LOG_DEBUG(" -> Audio device opened.\n");

    if (fenster_audio_available(&audio_device) < 0) {
        LOG_ERROR("Audio device not available.");
        return 1;
    }
    LOG_DEBUG(" -> Audio device looks ready.\n");

    sts_mixer_init(&mixer, FENSTER_SAMPLE_RATE, STS_MIXER_SAMPLE_FORMAT_FLOAT);
    LOG_DEBUG(" -> Mixer initialized.\n");

    // Start audio thread
    if (pthread_create(&fa->audio_thread_id, NULL, audio_thread, fa) != 0) {
        LOG_ERROR("Could not create audio thread.\n");
        return 1;
    }
    LOG_DEBUG(" -> Audio thread started.\n");

    LOG_DEBUG(" * Audio Buffer size: %d bytes\n", AUDIO_BUFFER_SIZE);
    LOG_DEBUG(" * Audio Sample rate: %d Hz\n", FENSTER_SAMPLE_RATE);
    LOG_DEBUG(" * Audio voices: %d\n", STS_MIXER_VOICES);

    // Clear audio buffer
    memset(fa->audio_buffer, 0, AUDIO_BUFFER_SIZE * sizeof(float));

    // Create vector of samples
    fa->samples = pe_vector_new(free);

    LOG_DEBUG("Audio subsystem started. Jolly good!\n");
    return 0;
}

/*
** Kill audio engine
*/
void pe_audio_destroy(struct pe_audio *fa) {
    LOG_DEBUG(" * Destroying audio subsystem...\n");
    if (pthread_cancel(fa->audio_thread_id) != 0) {
        LOG_ERROR("Could not cancel audio thread.\n");
    }
    sts_mixer_shutdown(&mixer);
    fenster_audio_close(&audio_device);
    pe_vector_destroy(fa->samples);
    LOG_DEBUG("Audio subsystem destroyed.\n");
}

/*
** Expose audio functions to Wren
*/
void pe_audio_register_functions(struct pe_engine_state *engine_state) {
    pe_add_function(&engine_state->wren_functions, "main", "Sound",
                    "internal_load_ogg(_)", true, &pe_audio_load_sample);
    pe_add_function(&engine_state->wren_functions, "main", "Sound",
                    "internal_play(_,_,_,_)", true, &pe_audio_play);
}
