/**
 * \file src/audio/audio.c
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date July 21, 2021
 *
 * Copyright (C) Josue Teodoro Moreira
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "audio/audio.h"

/* We'll use CreateThread on windows so we don't need it */
#ifndef _WIN32
static pthread_t audio_stream_update_thread_id;
#endif /* _WIN32 */

#ifdef _WIN32
DWORD WINAPI
#else
static void *
#endif /* _WIN32 */
_update_audio_stream(void *__arg)
{
  struct D_audio_stream *temp_audio_stream = (struct D_audio_stream *)__arg;

  while (D_is_audio_stream_active(temp_audio_stream))
    D_sleep(0.1f);

  D_set_audio_stream_offset(temp_audio_stream, 0.0f);

#ifdef _WIN32
  return 0;
#endif /* _WIN32 */
}

struct D_audio *
D_init_audio()
{
  struct D_audio *new_audio = (struct D_audio *)malloc(sizeof(struct D_audio *));
  D_assert(new_audio, NULL);

  new_audio->device = alcOpenDevice(NULL);
  D_assert(new_audio->device, DERR_NOINIT("OpenAL: Device"));

  new_audio->context = alcCreateContext(new_audio->device, 0);
  if (!alcMakeContextCurrent(new_audio->context))
  {
    D_raise_error("OpenAL: Could not make context current");

    return NULL;
  }

  return new_audio;
}

void
D_end_audio(struct D_audio *__audio)
{
  D_assert_return_void(__audio, DERR_NOPARAM("__audio", "Audio can't be NULL"));

  alcMakeContextCurrent(NULL);
  if (__audio->context)
    alcDestroyContext(__audio->context);
  if (__audio->device)
    alcCloseDevice(__audio->device);
}

void
D_set_audio_gain(float __gain)
{
  alListenerf(AL_GAIN, __gain);
}

void
D_set_audio_position(vec3 __position)
{
  alListener3f(AL_POSITION, __position[0], __position[1], __position[2]);
}

struct D_audio_stream *
D_create_audio_stream(const char *__file_name,
                      float       __min_gain,
                      float       __max_gain,
                      float       __gain,
                      bool        __loop)
{
  struct D_audio_stream *new_audio_stream = (struct D_audio_stream *)malloc(sizeof(struct D_audio_stream));
  D_assert(new_audio_stream, NULL);

  new_audio_stream->samples = stb_vorbis_decode_filename(__file_name,
                                                         &new_audio_stream->channels,
                                                         &new_audio_stream->sample_rate,
                                                         &new_audio_stream->data);

  if (new_audio_stream->channels == 2)
    new_audio_stream->format = AL_FORMAT_STEREO16;
  else
    new_audio_stream->format = AL_FORMAT_MONO16;

  alGenBuffers(1, &new_audio_stream->buffer);
  alBufferData(new_audio_stream->buffer, new_audio_stream->format, new_audio_stream->data,
               new_audio_stream->samples * 2 * sizeof(short), new_audio_stream->sample_rate);

  alGenSources(1, &new_audio_stream->source);
  alSourceQueueBuffers(new_audio_stream->source, 1, &new_audio_stream->buffer);

  new_audio_stream->min_gain = __min_gain;
  new_audio_stream->max_gain = __max_gain;
  alSourcef(new_audio_stream->source, AL_MIN_GAIN, new_audio_stream->min_gain);
  alSourcef(new_audio_stream->source, AL_MAX_GAIN, new_audio_stream->max_gain);
  D_set_audio_stream_gain(new_audio_stream, __gain);
  D_set_audio_stream_loop(new_audio_stream, __loop);

  return new_audio_stream;
}

void
D_end_audio_stream(struct D_audio_stream *__audio_stream)
{
  D_assert_return_void(__audio_stream, DERR_NOPARAM("__audio_stream", "Audio stream can't be NULL"));

  alDeleteSources(1, &__audio_stream->source);
  alDeleteBuffers(1, &__audio_stream->buffer);

  free(__audio_stream->data);
  free(__audio_stream);
}

void
D_play_audio_stream(struct D_audio_stream *__audio_stream)
{
  if (!__audio_stream)
    return;

  unsigned int old_state = __audio_stream->state;
  alSourcePlay(__audio_stream->source);
  if (old_state == AL_PAUSED)
    return;

  /* Thread will wait until source ends */
#ifdef _WIN32
  HANDLE thread = CreateThread(NULL, 0, _update_audio_stream, (void *)__audio_stream, 0, NULL);
  CloseHandle(thread);
#else
  pthread_create(&audio_stream_update_thread_id, NULL, _update_audio_stream, (void *)__audio_stream);
  pthread_exit(NULL);
#endif /* _WIN32 */
}

void
D_pause_audio_stream(struct D_audio_stream *__audio_stream)
{
  if (!__audio_stream)
    return;

  alSourcePause(__audio_stream->source);
}

void
D_stop_audio_stream(struct D_audio_stream *__audio_stream)
{
  if (!__audio_stream)
    return;

  alSourceStop(__audio_stream->source);
  alSourceUnqueueBuffers(__audio_stream->source, 1, &__audio_stream->buffer);
}

bool
D_is_audio_stream_active(struct D_audio_stream *__audio_stream)
{
  if (!__audio_stream)
    return AL_STOPPED;
  
  alGetSourcei(__audio_stream->source, AL_SOURCE_STATE, &__audio_stream->state);

  return __audio_stream->state != AL_STOPPED;
}

void
D_set_audio_stream_gain(struct D_audio_stream *__audio_stream,
                        float                  __gain)
{
  if (!__audio_stream)
    return;

  if (__gain <= 0.0f ||
      __gain <= __audio_stream->min_gain ||
      __gain >= __audio_stream->max_gain)
    return;

  alSourcef(__audio_stream->source, AL_GAIN, __gain);
  __audio_stream->gain = __gain;
}

void
D_set_audio_stream_loop(struct D_audio_stream *__audio_stream,
                        bool                   __loop)
{
  if (!__audio_stream)
    return;

  alSourcei(__audio_stream->source, AL_LOOPING, __loop);
}

void
D_set_audio_stream_position(struct D_audio_stream *__audio_stream,
                            vec3                   __position)
{
  if (!__audio_stream)
    return;

  alSource3f(__audio_stream->source, AL_POSITION, __position[0], __position[1], __position[3]);
}

void
D_set_audio_stream_offset(struct D_audio_stream *__audio_stream,
                          float                  __offset)
{
  if (!__audio_stream)
    return;

  alSourcef(__audio_stream->source, AL_SEC_OFFSET, __offset);
}
