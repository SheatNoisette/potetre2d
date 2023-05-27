#ifndef __AUDIO_H__
#define __AUDIO_H__

#include <stdint.h>
#include <pthread.h>

#include "engine.h"
#include "utils_vec.h"

// Audio buffer size
#define AUDIO_BUFFER_SIZE 128

struct pe_audio {
    struct pe_vector *samples;
    pthread_t audio_thread_id;
    float audio_buffer[AUDIO_BUFFER_SIZE];
};

int pe_audio_start(struct pe_audio *fa);
void pe_audio_destroy(struct pe_audio *fa);
void pe_audio_register_functions(struct pe_engine_state *engine_state);

#endif /* __AUDIO_H__ */
