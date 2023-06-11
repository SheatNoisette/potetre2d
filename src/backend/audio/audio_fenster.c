#if OS_WINDOWS
#define FENSTER_AUDIO_BUFSZ (AUDIO_BUFFER_SIZE)
#else
#define FENSTER_AUDIO_BUFSZ (AUDIO_BUFFER_SIZE * 2)
#endif
#include "fenster_audio.h"

/*
** Global audio state
**
** You shouldn't have more than one audio context or
** you're gonna have a bad time
*/
struct fenster_audio audio_device;

pthread_t audio_thread_id;
pthread_mutex_t audio_mutex; /* Avoid collisions when pushing samples */

/*
** Audio subsystem
** I hate audio programming, this is a mess
*/

/*
** Audio thread worker
*/
// Thread for audio device
void *audio_thread(void *arg) {

    LOG_DEBUG("Audio thread started!\n");

    struct pe_audio *fa = (struct pe_audio *)arg;
    for (;;) {
        // Wait for mutex audio_mutex or else we could get wonky audio
        pthread_mutex_lock(&audio_mutex);

        // Check if we should stop
        if (!fa->running) {
            pthread_mutex_unlock(&audio_mutex);
            break;
        }

        // Mix audio
        sts_mixer_mix_audio(&fa->mixer, fa->audio_buffer, AUDIO_BUFFER_SIZE);
        pthread_mutex_unlock(&audio_mutex);

        // Send to audio device
        fenster_audio_write(&audio_device, fa->audio_buffer, AUDIO_BUFFER_SIZE);
    }

    LOG_DEBUG("Audio thread stopped!\n");

    return NULL;
}

int pe_audio_backend_start(struct pe_audio *fa) {

    LOG_DEBUG(" - Backend: Fenster\n");
    LOG_DEBUG(" - Audio Buffer size: %d bytes\n", AUDIO_BUFFER_SIZE);
    LOG_DEBUG(" - Audio Sample rate: %d Hz\n", FENSTER_SAMPLE_RATE);

    if (fenster_audio_open(&audio_device) < 0) {
        LOG_ERROR("Could not open audio device\n");
        return 1;
    }
    LOG_DEBUG(" - Audio device opened.\n");

    if (fenster_audio_available(&audio_device) < 0) {
        LOG_ERROR("Audio device not available.");
        return 1;
    }
    LOG_DEBUG(" - Audio device looks ready.\n");

    sts_mixer_init(&fa->mixer, FENSTER_SAMPLE_RATE, STS_MIXER_SAMPLE_FORMAT_FLOAT);
    LOG_DEBUG(" - Mixer initialized.\n");

    // Start audio thread
    if (pthread_create(&audio_thread_id, NULL, audio_thread, fa) != 0) {
        LOG_ERROR("Could not create audio thread.\n");
        return 1;
    }
    LOG_DEBUG(" - Audio thread started.\n");

    // Set running flag
    fa->running = true;

    // Create mutex for audio buffer (audio_mutex)
    if (pthread_mutex_init(&audio_mutex, NULL) != 0) {
        LOG_ERROR("Could not create audio mutex.\n");
        return 1;
    }

    return 0;
}

// Play a sound
int pe_audio_backend_play(struct pe_audio *fa, sts_mixer_sample_t *sample,
                          float volume, float pitch, float pan) {

    // Lock audio to add sample
    pthread_mutex_lock(&audio_mutex);
    sts_mixer_play_sample(&fa->mixer, sample, volume, pitch, pan);
    pthread_mutex_unlock(&audio_mutex);

    return 0;
}

// Destroy what the backend created
int pe_audio_backend_destroy(struct pe_audio *fa) {
    // Stop audio thread
    pthread_mutex_lock(&audio_mutex);
    fa->running = false;
    pthread_mutex_unlock(&audio_mutex);
    fenster_audio_close(&audio_device);

    return 0;
}
