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

struct D_audio_stream *
D_create_audio_stream(const char *__file_name)
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
  alSourcePlay(new_audio_stream->source);

  while (D_is_audio_stream_playing(new_audio_stream))
    Sleep(50);

  return new_audio_stream;
}

void
D_end_audio_stream(struct D_audio_stream *__audio_stream)
{
  D_assert_return_void(__audio_stream, DERR_NOPARAM("__audio_stream", "Audio stream can't be NULL"));

  free(__audio_stream->data);
  free(__audio_stream);
}

bool
D_is_audio_stream_playing(struct D_audio_stream *__audio_stream)
{
  if (__audio_stream)
    alGetSourcei(__audio_stream->source, AL_SOURCE_STATE, &__audio_stream->state);
  else
    __audio_stream->state = false;

  return __audio_stream->state;
}
