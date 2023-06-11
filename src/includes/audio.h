#ifndef __AUDIO_H__
#define __AUDIO_H__

#include <stdint.h>
#include <pthread.h>

#include "engine.h"
#include "utils_vec.h"

#define STS_MIXER_IMPLEMENTATION
#include "sts_mixer_mono.h"

// Audio buffer size
#define AUDIO_BUFFER_SIZE 8192

struct pe_audio {
    bool running; /* Audio running state, if audio system should stop */
    struct pe_vector *samples;
    sts_mixer_t mixer;
    float audio_buffer[AUDIO_BUFFER_SIZE + 1];
};

int pe_audio_start(struct pe_audio *fa);
void pe_audio_destroy(struct pe_audio *fa);
void pe_audio_register_functions(struct pe_engine_state *engine_state);

#endif /* __AUDIO_H__ */
