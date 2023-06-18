#include <math.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if OS_WINDOWS
#include <windows.h>
#include <mmsystem.h>
#elif OS_MACOS
#include <alloca.h>
#endif

#include "audio.h"
#include "engine.h"
#include "log.h"
#include "utils_vec.h"
#include "utils.h"

#include "wren.h"
#include "stb_vorbis.h"

// Audio backends
// Why we don't do a struct of function pointers? Because this will bloat the
// executable size for no reason. We only need one backend at a time.
#if ENGINE_AUDIO_BACKEND_FENSTER
#include "backend/audio/audio_fenster.c"
#elif ENGINE_AUDIO_BACKEND_NONE
#include "backend/audio/audio_none.c"
#elif ENGINE_AUDIO_BACKEND_SDL2
#include "backend/audio/audio_sdl2.c"
#else
#error "No audio backend selected"
#endif

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
** Free sample from memory
*/
static void free_sample(void *sample) {
    sts_mixer_sample_t *sts_sample = (sts_mixer_sample_t *)sample;
    free(sts_sample->data);
    free(sts_sample);
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
    pe_audio_backend_play(engine->audio, sample, volume, pitch, pan);

    wrenSetSlotDouble(vm, 0, 0.);
}

/*
** Start audio
*/
int pe_audio_start(struct pe_audio *fa) {

    // Create vector of samples
    fa->samples = pe_vector_new(free_sample);

    if (pe_audio_backend_start(fa) != 0) {
        LOG_ERROR(" - Could not start audio backend!\n");
        return 1;
    }

    return 0;
}

/*
** Destroy audio
*/
void pe_audio_destroy(struct pe_audio *fa) {
    pe_audio_backend_destroy(fa);
    pe_vector_destroy(fa->samples);
    LOG_DEBUG(" - Audio backend destroyed.\n");
}

/*
** Register audio functions
*/
void pe_audio_register_functions(struct pe_engine_state *engine_state) {
    pe_add_function(&engine_state->wren_functions, "main", "Sound",
                    "internal_load_ogg(_)", true, &pe_audio_load_sample);
    pe_add_function(&engine_state->wren_functions, "main", "Sound",
                    "internal_play(_,_,_,_)", true, &pe_audio_play);
}
