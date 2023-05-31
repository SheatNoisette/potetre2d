#ifndef __AUDIO_H__
#define __AUDIO_H__

#include <stdint.h>
#include <pthread.h>

#include "engine.h"
#include "utils_vec.h"

// Audio buffer size
#if OS_WINDOWS
#define AUDIO_BUFFER_SIZE 8192
#else
#define AUDIO_BUFFER_SIZE 32
#endif

struct pe_audio {
    bool running; /* Audio running state, if audio system should stop */
    struct pe_vector *samples;
    pthread_t audio_thread_id;
    pthread_mutex_t audio_mutex; /* Avoid collisions when pushing samples */
    float audio_buffer[AUDIO_BUFFER_SIZE + 1];
};

int pe_audio_start(struct pe_audio *fa);
void pe_audio_destroy(struct pe_audio *fa);
void pe_audio_register_functions(struct pe_engine_state *engine_state);

#endif /* __AUDIO_H__ */
