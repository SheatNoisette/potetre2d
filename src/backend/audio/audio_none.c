// Init what's needed
int pe_audio_backend_start(struct pe_audio *fa) {
    (void)fa;
    LOG_DEBUG(" - Backend: Null audio\n");
    return 0;
}

// Play a sound
int pe_audio_backend_play(struct pe_audio *fa, sts_mixer_sample_t *sample,
                          float volume, float pitch, float pan) {
    (void)fa;
    (void)sample;
    (void)volume;
    (void)pitch;
    (void)pan;
    LOG_DEBUG("Asked to play sample at %f volume, %f pitch, %f pan on Null backend!\n", volume, pitch, pan);
    return 0;
}

// Destroy what the backend created
int pe_audio_backend_destroy(struct pe_audio *fa) {
    (void)fa;
    return 0;
}
