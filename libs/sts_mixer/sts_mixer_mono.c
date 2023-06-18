#include <math.h>

#include "sts_mixer_mono.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
////
////    IMPLEMENTATION
////
////

static float sts_mixer__clamp(const float value, const float min,
                              const float max) {
    if (value < min)
        return min;
    else if (value > max)
        return max;
    else
        return value;
}

static float sts_mixer__clamp_sample(const float sample) {
    if (sample < -1.0f)
        return -1.0f;
    else if (sample > 1.0f)
        return 1.0f;
    else
        return sample;
}

static float sts_mixer__get_sample(sts_mixer_sample_t *sample,
                                   unsigned int position) {
    switch (sample->audio_format) {
    case STS_MIXER_SAMPLE_FORMAT_8:
        return (float)((char *)sample->data)[position] / 127.0f;
    case STS_MIXER_SAMPLE_FORMAT_16:
        return (float)((short *)sample->data)[position] / 32767.0f;
    case STS_MIXER_SAMPLE_FORMAT_32:
        return (float)((int *)sample->data)[position] / 2147483647.0f;
    case STS_MIXER_SAMPLE_FORMAT_FLOAT:
        return ((float *)sample->data)[position];
    default:
        return 0.0f;
    }
}

static void sts_mixer__reset_voice(sts_mixer_t *mixer, const int i) {
    sts_mixer_voice_t *voice = &mixer->voices[i];
    voice->state = STS_MIXER_VOICE_STOPPED;
    voice->sample = 0;
    voice->stream = 0;
    voice->position = voice->gain = voice->pitch = voice->pan = 0.0f;
}

static int sts_mixer__find_free_voice(sts_mixer_t *mixer) {
    int i;

    for (i = 0; i < STS_MIXER_VOICES; ++i) {
        if (mixer->voices[i].state == STS_MIXER_VOICE_STOPPED)
            return i;
    }
    return -1;
}

void sts_mixer_init(sts_mixer_t *mixer, unsigned int frequency,
                    int audio_format) {
    int i;

    for (i = 0; i < STS_MIXER_VOICES; ++i)
        sts_mixer__reset_voice(mixer, i);
    mixer->frequency = frequency;
    mixer->gain = 1.0f;
    mixer->audio_format = audio_format;
    mixer->enable_mono = 0;
}

void sts_mixer_shutdown(sts_mixer_t *mixer) { sts_mixer_init(mixer, 0, 0); }

int sts_mixer_get_active_voices(sts_mixer_t *mixer) {
    int i, active;
    for (i = 0, active = 0; i < STS_MIXER_VOICES; ++i) {
        if (mixer->voices[i].state != STS_MIXER_VOICE_STOPPED)
            ++active;
    }
    return active;
}

int sts_mixer_play_sample(sts_mixer_t *mixer, sts_mixer_sample_t *sample,
                          float gain, float pitch, float pan) {
    int i;
    sts_mixer_voice_t *voice;

    i = sts_mixer__find_free_voice(mixer);
    if (i >= 0) {
        voice = &mixer->voices[i];
        voice->gain = gain;
        voice->pitch = sts_mixer__clamp(pitch, 0.1f, 10.0f);
        voice->pan = sts_mixer__clamp(pan * 0.5f, -0.5f, 0.5f);
        voice->position = 0.0f;
        voice->sample = sample;
        voice->stream = 0;
        voice->state = STS_MIXER_VOICE_PLAYING;
    }
    return i;
}

int sts_mixer_play_stream(sts_mixer_t *mixer, sts_mixer_stream_t *stream,
                          float gain) {
    int i;
    sts_mixer_voice_t *voice;

    i = sts_mixer__find_free_voice(mixer);
    if (i >= 0) {
        voice = &mixer->voices[i];
        voice->gain = gain;
        voice->position = 0.0f;
        voice->sample = 0;
        voice->stream = stream;
        voice->state = STS_MIXER_VOICE_STREAMING;
    }
    return i;
}

void sts_mixer_stop_voice(sts_mixer_t *mixer, int voice) {
    if (voice >= 0 && voice < STS_MIXER_VOICES)
        sts_mixer__reset_voice(mixer, voice);
}

void sts_mixer_stop_sample(sts_mixer_t *mixer, sts_mixer_sample_t *sample) {
    int i;

    for (i = 0; i < STS_MIXER_VOICES; ++i) {
        if (mixer->voices[i].sample == sample)
            sts_mixer__reset_voice(mixer, i);
    }
}

void sts_mixer_stop_stream(sts_mixer_t *mixer, sts_mixer_stream_t *stream) {
    int i;

    for (i = 0; i < STS_MIXER_VOICES; ++i) {
        if (mixer->voices[i].stream == stream)
            sts_mixer__reset_voice(mixer, i);
    }
}

void sts_mixer_mix_audio(sts_mixer_t *mixer, void *output,
                         unsigned int samples) {
    sts_mixer_voice_t *voice;
    unsigned int i, position;
    float left, right, advance, sample;
    char *out_8 = (char *)output;
    short *out_16 = (short *)output;
    int *out_32 = (int *)output;
    float *out_float = (float *)output;

    // mix all voices
    advance = 1.0f / (float)mixer->frequency;
    for (; samples > 0; --samples) {
        left = 0.0f;
        right = 0.0f;
        for (i = 0; i < STS_MIXER_VOICES; ++i) {
            voice = &mixer->voices[i];
            if (voice->state == STS_MIXER_VOICE_PLAYING) {
                position = (int)voice->position;
                if (position < voice->sample->length) {
                    sample = sts_mixer__clamp_sample(
                        sts_mixer__get_sample(voice->sample, position) *
                        voice->gain);
    if (!mixer->enable_mono) {
        
                    left +=
                        sts_mixer__clamp_sample(sample * (0.5f - voice->pan));
    }
                    right +=
                        sts_mixer__clamp_sample(sample * (0.5f + voice->pan));
                    voice->position += (float)voice->sample->frequency *
                                       advance * voice->pitch;
                } else
                    sts_mixer__reset_voice(mixer, i);
            } else if (voice->state == STS_MIXER_VOICE_STREAMING) {
                position = ((int)voice->position) * 2;
                if (position >= voice->stream->sample.length) {
                    // buffer empty...refill
                    voice->stream->callback(&voice->stream->sample,
                                            voice->stream->userdata);
                    voice->position = 0.0f;
                    position = 0;
                }
if (!mixer->enable_mono) {
                left += sts_mixer__clamp_sample(
                    sts_mixer__get_sample(&voice->stream->sample, position) *
                    voice->gain);
}
                right += sts_mixer__clamp_sample(
                    sts_mixer__get_sample(&voice->stream->sample,
                                          position + 1) *
                    voice->gain);
                voice->position +=
                    (float)voice->stream->sample.frequency * advance;
            }
        }

        // write to buffer
if (!mixer->enable_mono) {
        left = sts_mixer__clamp_sample(left);
}
        right = sts_mixer__clamp_sample(right);
        switch (mixer->audio_format) {
        case STS_MIXER_SAMPLE_FORMAT_8:
if (!mixer->enable_mono) {
            *out_8++ = (char)(left * 127.0f);
}
            *out_8++ = (char)(right * 127.0f);
            break;
        case STS_MIXER_SAMPLE_FORMAT_16:
if (!mixer->enable_mono) {
            *out_16++ = (short)(left * 32767.0f);
}
            *out_16++ = (short)(right * 32767.0f);
            break;
        case STS_MIXER_SAMPLE_FORMAT_32:
if (!mixer->enable_mono) {
            *out_32++ = (int)(left * 2147483647.0f);
            }
            *out_32++ = (int)(right * 2147483647.0f);
            break;
        case STS_MIXER_SAMPLE_FORMAT_FLOAT:
if (!mixer->enable_mono) {
            *out_float++ = left;
            }
            *out_float++ = right;
            break;
        }
    }
}
/*
  This is free and unencumbered software released into the public domain.

  Anyone is free to copy, modify, publish, use, compile, sell, or
  distribute this software, either in source code form or as a compiled
  binary, for any purpose, commercial or non-commercial, and by any
  means.

  In jurisdictions that recognize copyright laws, the author or authors
  of this software dedicate any and all copyright interest in the
  software to the public domain. We make this dedication for the benefit
  of the public at large and to the detriment of our heirs and
  successors. We intend this dedication to be an overt act of
  relinquishment in perpetuity of all present and future rights to this
  software under copyright law.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
  OTHER DEALINGS IN THE SOFTWARE.

  For more information, please refer to <http://unlicense.org/>
*/
