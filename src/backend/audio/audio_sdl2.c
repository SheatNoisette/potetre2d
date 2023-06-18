/*
** SDL2 Audio backend
*/

#include <SDL2/SDL.h>

struct audio_backend_sdl2 {
    SDL_AudioDeviceID device;
    SDL_AudioSpec spec;
    SDL_AudioSpec obtained;
    sts_mixer_t mixer;
};

static struct audio_backend_sdl2 global_ab_sdl2;

// Callback for SDL2 audio device
void ab_sdl2_callback(void *userdata, Uint8 *stream, int len) {
    (void)userdata;
    (void)len;
    sts_mixer_mix_audio(&global_ab_sdl2.mixer, (Uint8 *)stream, len / (sizeof(int) * 2));
}

// Init what's needed
int pe_audio_backend_start(struct pe_audio *fa) {
    (void)fa;
    LOG_DEBUG(" - Backend: SDL2\n");
    LOG_DEBUG(" - Audio Buffer size: %d bytes\n", AUDIO_BUFFER_SIZE);

    // Init SDL2 audio
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        LOG_ERROR(" - Could not init SDL2 audio: %s\n", SDL_GetError());
        return -1;
    }

    // Set up audio spec
    global_ab_sdl2.spec.format = AUDIO_S32SYS;
    global_ab_sdl2.spec.freq = AUDIO_SAMPLE_RATE;
    global_ab_sdl2.spec.channels = 2;
    global_ab_sdl2.spec.userdata = NULL;
    global_ab_sdl2.spec.samples = AUDIO_BUFFER_SIZE;
    global_ab_sdl2.spec.callback = ab_sdl2_callback;

    // Open audio device
    global_ab_sdl2.device = SDL_OpenAudioDevice(NULL, 0, &global_ab_sdl2.spec,
                                                &global_ab_sdl2.obtained, 0);

    // Check if we got a device
    if (global_ab_sdl2.device == 0) {
        LOG_ERROR(" - Could not open audio device: %s\n", SDL_GetError());
        return -1;
    }

    // List some info about the device
    LOG_DEBUG(" - Audio device opened.\n");
    LOG_DEBUG(" - Audio device name: \"%s\"\n", SDL_GetAudioDeviceName(0, 0));
    LOG_DEBUG(" - Audio device freq: %d\n", global_ab_sdl2.obtained.freq);
    LOG_DEBUG(" - Audio device channels: %d\n", global_ab_sdl2.obtained.channels);
    LOG_DEBUG(" - Audio device samples: %d\n", global_ab_sdl2.obtained.samples);

    // Check if we got the right format we wanted
    if (global_ab_sdl2.obtained.format != AUDIO_S32SYS) {
        LOG_ERROR(" - Could not get the right audio format.\n");
        return -1;
    }

    // Init mixer
    sts_mixer_init(&global_ab_sdl2.mixer, AUDIO_SAMPLE_RATE, STS_MIXER_SAMPLE_FORMAT_32);
    global_ab_sdl2.mixer.enable_mono = 0;

    // Start audio device
    SDL_PauseAudioDevice(global_ab_sdl2.device, 0);

    return 0;
}

// Play a sound
int pe_audio_backend_play(struct pe_audio *fa, sts_mixer_sample_t *sample,
                          float volume, float pitch, float pan) {
    (void)fa;
    SDL_LockAudioDevice(global_ab_sdl2.device);
    sts_mixer_play_sample(&global_ab_sdl2.mixer, sample, volume, pitch, pan);
    SDL_UnlockAudioDevice(global_ab_sdl2.device);
    return 0;
}

// Destroy what the backend created
int pe_audio_backend_destroy(struct pe_audio *fa) {
    (void)fa;
    LOG_DEBUG(" - Destroying SDL2 audio backend.\n");
    SDL_PauseAudioDevice(global_ab_sdl2.device, 1);
    SDL_CloseAudioDevice(global_ab_sdl2.device);
    LOG_DEBUG(" - SDL2 audio backend destroyed.\n");
    SDL_Quit();
    LOG_DEBUG(" - SDL2 audio quit.\n");
    return 0;
}
