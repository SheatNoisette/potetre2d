#include "fenster_audio.h"

/*
** Global audio state
**
** You shouldn't have more than one audio context or
** you're gonna have a bad time
*/
struct audio_backend_fenster {
    struct fenster_audio audio_device;
    pthread_t audio_thread_id;
    pthread_mutex_t audio_mutex; /* Avoid collisions when pushing samples */
    sts_mixer_t mixer;
    float audio_buffer[AUDIO_BUFFER_SIZE + 1];
    bool running; /* Audio running state, if audio system should stop */
};

// Global audio state
static struct audio_backend_fenster global_ab_fenster;

/*
** Audio thread worker
*/
// Thread for audio device
void *ab_fenster_thread(void *arg) {
    (void)arg;
    LOG_DEBUG(" - Audio thread worker running...\n");
    for (;;) {
        // Wait for mutex audio_mutex or else we could get wonky audio
        pthread_mutex_lock(&global_ab_fenster.audio_mutex);

        // Check if we should stop
        if (!global_ab_fenster.running) {
            pthread_mutex_unlock(&global_ab_fenster.audio_mutex);
            break;
        }

        // Mix audio
        sts_mixer_mix_audio(&global_ab_fenster.mixer,
                            global_ab_fenster.audio_buffer, AUDIO_BUFFER_SIZE);
        pthread_mutex_unlock(&global_ab_fenster.audio_mutex);

        // Send to audio device
        fenster_audio_write(&global_ab_fenster.audio_device,
                            global_ab_fenster.audio_buffer, AUDIO_BUFFER_SIZE);
    }

    LOG_DEBUG(" - Audio thread worker stopped (clean exit)!\n");

    return NULL;
}

int pe_audio_backend_start(struct pe_audio *fa) {

    LOG_DEBUG(" - Backend: Fenster\n");
    LOG_DEBUG(" - Audio Buffer size: %d bytes\n", AUDIO_BUFFER_SIZE);
    LOG_DEBUG(" - Audio Sample rate: %d Hz\n", FENSTER_SAMPLE_RATE);

    if (fenster_audio_open(&global_ab_fenster.audio_device) < 0) {
        LOG_ERROR("Could not open audio device\n");
        return 1;
    }
    LOG_DEBUG(" - Audio device opened.\n");

    if (fenster_audio_available(&global_ab_fenster.audio_device) < 0) {
        LOG_ERROR("Audio device not available.");
        return 1;
    }
    LOG_DEBUG(" - Audio device looks ready.\n");

    sts_mixer_init(&global_ab_fenster.mixer, FENSTER_SAMPLE_RATE,
                   STS_MIXER_SAMPLE_FORMAT_FLOAT);
    global_ab_fenster.mixer.enable_mono = 1; // Set mono mixing
    global_ab_fenster.running = false;       // Wait for thread to start
    LOG_DEBUG(" - Mixer initialized.\n");

    // Create mutex for audio buffer (audio_mutex)
    if (pthread_mutex_init(&global_ab_fenster.audio_mutex, NULL) != 0) {
        LOG_ERROR("Could not create audio mutex.\n");
        return 1;
    }
    LOG_DEBUG(" - Audio mutex created.\n");

    // Start audio thread
    if (pthread_create(&global_ab_fenster.audio_thread_id, NULL,
                       ab_fenster_thread, fa) != 0) {
        LOG_ERROR("Could not create audio thread.\n");
        return 1;
    }
    LOG_DEBUG(" - Audio thread started.\n");

    // Set running flag
    global_ab_fenster.running = true;

    return 0;
}

// Play a sound
int pe_audio_backend_play(struct pe_audio *fa, sts_mixer_sample_t *sample,
                          float volume, float pitch, float pan) {
    (void)fa;
    // Lock audio to add sample
    pthread_mutex_lock(&global_ab_fenster.audio_mutex);
    sts_mixer_play_sample(&global_ab_fenster.mixer, sample, volume, pitch, pan);
    pthread_mutex_unlock(&global_ab_fenster.audio_mutex);

    return 0;
}

// Destroy what the backend created
int pe_audio_backend_destroy(struct pe_audio *fa) {
    (void)fa;
    // Stop audio thread
    pthread_mutex_lock(&global_ab_fenster.audio_mutex);
    global_ab_fenster.running = false;
    pthread_mutex_unlock(&global_ab_fenster.audio_mutex);
    fenster_audio_close(&global_ab_fenster.audio_device);

    return 0;
}
