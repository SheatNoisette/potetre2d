#ifndef FENSTER_AUDIO_H
#define FENSTER_AUDIO_H

#ifndef FENSTER_SAMPLE_RATE
#define FENSTER_SAMPLE_RATE 44100
#endif

#ifndef FENSTER_AUDIO_BUFSZ
#define FENSTER_AUDIO_BUFSZ 8192
#endif

#if defined(__APPLE__)
#include <AudioToolbox/AudioQueue.h>
struct fenster_audio {
  AudioQueueRef queue;
  size_t pos;
  float buf[FENSTER_AUDIO_BUFSZ];
  dispatch_semaphore_t drained;
  dispatch_semaphore_t full;
};
#elif defined(_WIN32)
#include <mmsystem.h>
#include <windows.h>
struct fenster_audio {
  WAVEHDR header;
  HWAVEOUT wo;
  WAVEHDR hdr[2];
  int16_t buf[FENSTER_AUDIO_BUFSZ];
};
#elif defined(__linux__)
struct fenster_audio {
  void *pcm;
  float buf[FENSTER_AUDIO_BUFSZ];
  size_t pos;
};
#endif

#ifndef FENSTER_API
#define FENSTER_API extern
#endif
FENSTER_API int fenster_audio_open(struct fenster_audio *f);
FENSTER_API int fenster_audio_available(struct fenster_audio *f);
FENSTER_API void fenster_audio_write(struct fenster_audio *f, float *buf,
                                     size_t n);
FENSTER_API void fenster_audio_close(struct fenster_audio *f);

#ifndef FENSTER_HEADER
#if defined(__APPLE__)
static void fenster_audio_cb(void *p, AudioQueueRef q, AudioQueueBufferRef b) {
  struct fenster_audio *fa = (struct fenster_audio *)p;
  dispatch_semaphore_wait(fa->full, DISPATCH_TIME_FOREVER);
  memmove(b->mAudioData, fa->buf, sizeof(fa->buf));
  dispatch_semaphore_signal(fa->drained);
  AudioQueueEnqueueBuffer(q, b, 0, NULL);
}
FENSTER_API int fenster_audio_open(struct fenster_audio *fa) {
  AudioStreamBasicDescription format = {0};
  format.mSampleRate = FENSTER_SAMPLE_RATE;
  format.mFormatID = kAudioFormatLinearPCM;
  format.mFormatFlags = kLinearPCMFormatFlagIsFloat | kAudioFormatFlagIsPacked;
  format.mBitsPerChannel = 32;
  format.mFramesPerPacket = format.mChannelsPerFrame = 1;
  format.mBytesPerPacket = format.mBytesPerFrame = 4;
  fa->drained = dispatch_semaphore_create(1);
  fa->full = dispatch_semaphore_create(0);
  AudioQueueNewOutput(&format, fenster_audio_cb, fa, NULL, NULL, 0, &fa->queue);
  for (int i = 0; i < 2; i++) {
    AudioQueueBufferRef buffer = NULL;
    AudioQueueAllocateBuffer(fa->queue, FENSTER_AUDIO_BUFSZ * 4, &buffer);
    buffer->mAudioDataByteSize = FENSTER_AUDIO_BUFSZ * 4;
    memset(buffer->mAudioData, 0, buffer->mAudioDataByteSize);
    AudioQueueEnqueueBuffer(fa->queue, buffer, 0, NULL);
  }
  AudioQueueStart(fa->queue, NULL);
  return 0;
}
FENSTER_API void fenster_audio_close(struct fenster_audio *fa) {
  AudioQueueStop(fa->queue, false);
  AudioQueueDispose(fa->queue, false);
}
FENSTER_API int fenster_audio_available(struct fenster_audio *fa) {
  if (dispatch_semaphore_wait(fa->drained, DISPATCH_TIME_NOW))
    return 0;
  return FENSTER_AUDIO_BUFSZ - fa->pos;
}
FENSTER_API void fenster_audio_write(struct fenster_audio *fa, float *buf,
                                     size_t n) {
  while (fa->pos < FENSTER_AUDIO_BUFSZ && n > 0) {
    fa->buf[fa->pos++] = *buf++, n--;
  }
  if (fa->pos >= FENSTER_AUDIO_BUFSZ) {
    fa->pos = 0;
    dispatch_semaphore_signal(fa->full);
  }
}
#elif defined(_WIN32)

FENSTER_API int fenster_audio_open(struct fenster_audio *fa) {
  WAVEFORMATEX wfx;
  wfx.wFormatTag = WAVE_FORMAT_PCM;
  wfx.nChannels = 1;
  wfx.nSamplesPerSec = FENSTER_SAMPLE_RATE;
  wfx.wBitsPerSample = 16;
  wfx.nBlockAlign = wfx.nChannels * wfx.wBitsPerSample / 8;
  wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
  wfx.cbSize = 0;

  // Error checking
  MMRESULT result;

  if ((result = waveOutOpen(&fa->wo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL)) !=
      MMSYSERR_NOERROR) {
    if (result == MMSYSERR_ALLOCATED) {
      MessageBox(NULL, "WAVE_MAPPER is already allocated", "Error", MB_OK);
    } else if (result == MMSYSERR_BADDEVICEID) {
      MessageBox(NULL, "The specified device identifier is out of range.",
                 "Error", MB_OK);
    } else if (result == MMSYSERR_NODRIVER) {
      MessageBox(NULL, "There is no audio driver in this system.", "Error",
                 MB_OK);
    } else if (result == MMSYSERR_NOMEM) {
      MessageBox(NULL, "Unable to allocate or lock memory.", "Error", MB_OK);
    } else if (result == WAVERR_BADFORMAT) {
      MessageBox(NULL,
                 "Attempted to open with an unsupported waveform-audio "
                 "format.",
                 "Error", MB_OK);
    } else if (result == WAVERR_SYNC) {
      MessageBox(NULL,
                 "The device is synchronous but waveOutOpen was called "
                 "without using the WAVE_ALLOWSYNC flag.",
                 "Error", MB_OK);
    } else {
      MessageBox(NULL, "Unknown error", "Error", MB_OK);
    }
    return 1;
  }
  return 0;
}
FENSTER_API int fenster_audio_available(struct fenster_audio *fa) {
  // Check if the buffer is ready to be written to
  for (int i = 0; i < 2; i++) {
    if (fa->hdr[i].dwFlags & WHDR_DONE) {
      return FENSTER_AUDIO_BUFSZ;
    }
  }

  return 0;
}
FENSTER_API void fenster_audio_write(struct fenster_audio *fa, float *buf,
                                     size_t n) {

  WAVEHDR header = {0};
  header.lpData = (LPSTR)fa->buf;
  header.dwBufferLength = n;
  // Send the buffer to the audio device and wait for it to finish
  for (int j = 0; j < n; j++) {
    fa->buf[j] = buf[j] * 32767;
  }
  waveOutPrepareHeader(fa->wo, &header, sizeof(WAVEHDR));
  waveOutWrite(fa->wo, &header, sizeof(WAVEHDR));
  while (waveOutUnprepareHeader(fa->wo, &header, sizeof(WAVEHDR)) ==
         WAVERR_STILLPLAYING)
    ;
}
FENSTER_API void fenster_audio_close(struct fenster_audio *fa) {
  waveOutClose(fa->wo);
}
#elif defined(__linux__)
int snd_pcm_open(void **, const char *, int, int);
int snd_pcm_set_params(void *, int, int, int, int, int, int);
int snd_pcm_avail(void *);
int snd_pcm_writei(void *, const void *, unsigned long);
int snd_pcm_recover(void *, int, int);
int snd_pcm_close(void *);
FENSTER_API int fenster_audio_open(struct fenster_audio *fa) {
  if (snd_pcm_open(&fa->pcm, "default", 0, 0))
    return -1;
  int fmt = (*(unsigned char *)(&(uint16_t){1})) ? 14 : 15;
  return snd_pcm_set_params(fa->pcm, fmt, 3, 1, FENSTER_SAMPLE_RATE, 1, 100000);
}
FENSTER_API int fenster_audio_available(struct fenster_audio *fa) {
  int n = snd_pcm_avail(fa->pcm);
  if (n < 0)
    snd_pcm_recover(fa->pcm, n, 0);
  return n;
}
FENSTER_API void fenster_audio_write(struct fenster_audio *fa, float *buf,
                                     size_t n) {
  int r = snd_pcm_writei(fa->pcm, buf, n);
  if (r < 0)
    snd_pcm_recover(fa->pcm, r, 0);
}
FENSTER_API void fenster_audio_close(struct fenster_audio *fa) {
  snd_pcm_close(fa->pcm);
}
#endif

#endif /* FENSTER_HEADER */
#endif /* FENSTER_AUDIO_H */
