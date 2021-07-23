/**
 * \file inc/audio/audio.h
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date July 21, 2021
 *
 * \brief Audio related utilities
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

#ifndef __D_AUDIO_H__
#define __D_AUDIO_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "core/core.h"
#define STB_VORBIS_HEADER_ONLY
#include "audio/stb_vorbis.c"
#include "AL/al.h"
#include "AL/alc.h"
#include "cglm/vec3.h"
#ifndef _WIN32
#include <pthread.h>
#endif /* _WIN32 */

struct D_audio
{
  ALCdevice *device;
  ALCcontext *context;
};

struct D_audio_stream
{
  int channels, sample_rate, samples;
  short *data;

  unsigned int buffer, source, format, state;
  float gain, min_gain, max_gain;
};

struct D_audio *
D_init_audio();

void
D_end_audio();

void
D_set_audio_gain(float __gain);

void
D_set_audio_position(vec3 __position);

struct D_audio_stream *
D_create_audio_stream(const char *__file_name,
                      float       __min_gain,
                      float       __max_gain,
                      float       __gain,
                      bool        __loop);

void
D_end_audio_stream(struct D_audio_stream *__audio_stream);

void
D_play_audio_stream(struct D_audio_stream *__audio_stream);

void
D_pause_audio_stream(struct D_audio_stream *__audio_stream);

void
D_stop_audio_stream(struct D_audio_stream *__audio_stream);

bool
D_is_audio_stream_active(struct D_audio_stream *__audio_stream);

void
D_set_audio_stream_gain(struct D_audio_stream *__audio_stream,
                        float                  __gain);

void
D_set_audio_stream_loop(struct D_audio_stream *__audio_stream,
                        bool                   __loop);

void
D_set_audio_stream_position(struct D_audio_stream *__audio_stream,
                            vec3                   __position);

void
D_set_audio_stream_offset(struct D_audio_stream *__audio_stream,
                          float                  __offset);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_AUDIO_H__ */
