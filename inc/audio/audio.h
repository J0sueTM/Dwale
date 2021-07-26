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

#ifdef _WIN32
#include "AL/al.h"
#include "AL/alc.h"
#else
#include <AL/al.h>
#include <AL/alc.h>
#include <pthread.h>
#endif /* _win32 */
#include "cglm/vec3.h"

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

/**
 * \brief initializes and prepare general audio.
 */
struct D_audio *
D_init_audio();

/**
 * \brief Ends general audio and submodules.
 */
void
D_end_audio();

/**
 * \brief Sets general audio (mixer)'s gain.
 *
 * \param __gain Specifies the new gain.
 */
void
D_set_audio_gain(float __gain);

/**
 * \brief Sets general audio's position relative to the center
 *        of the listener.
 *
 *  \param __position Specifies the new position;
 */
void
D_set_audio_position(vec3 __position);

/**
 * \brief Creates a streamable audio source than can be
 *        be played by the general audio with openal.
 *
 * \param __file_name Specifies the path to the file cointaining
 *                    the .ogg audio.
 *  \param __min_gain Specifies the minimum gain that this stream
 *                    can reach.
 *  \param __max_gain Specifies the maximum gain that this stream
 *                    can reach.
 *  \param __gain     Specifies the actual that this stream will begin with.
 *  \param __loop     Specifies whether this stream will loop or not.
 *
 *  \return The newly created audio stream.
 */
struct D_audio_stream *
D_create_audio_stream(const char *__file_name,
                      float       __min_gain,
                      float       __max_gain,
                      float       __gain,
                      bool        __loop);

/**
 * \brief Ends an audio stream.
 *
 * \param __audio_stream Specifies the audio stream to be ended.
 */
void
D_end_audio_stream(struct D_audio_stream *__audio_stream);

/**
 * \brief Plays an audio stream.
 *
 * \param __audio_stream Specifies the audio stream to be played.
 *                       NOTE(all): If it's already playing or paused,
 *                       OpenAL will continue where it paused or is already
 *                       playing.
 */
void
D_play_audio_stream(struct D_audio_stream *__audio_stream);

/**
 * \brief Pauses an audio stream.
 *
 * \param __audio_stream Specifies the audio stream to be paused.
 */
void
D_pause_audio_stream(struct D_audio_stream *__audio_stream);

/**
 * \brief Stops an audio stream.
 *
 * \param __audio_stream Specifies the audio stream to be stopped.
 *                       NOTE(all): If you stop an audio, it can't
 *                       be resumed, if you play it again, it will
 *                       rewind to the beginning.
 */
void
D_stop_audio_stream(struct D_audio_stream *__audio_stream);

/**
 * \brief Whether an audio stream is active or not.
 *        NOTE(all): By active, I mean if it's state is
 *        whether AL_PLAYING or AL_PAUSED.
 *
 * \param __audio_stream Specifies the audio stream whose state
 *                       will be checked.
 */
bool
D_is_audio_stream_active(struct D_audio_stream *__audio_stream);

/**
 * \brief Sets the gain of an audio stream.
 *
 * \param __audio_stream Specifies the audio stream whose
 *                       gain will be changed.
 * \param __gain         Specifies the new gain.
 */
void
D_set_audio_stream_gain(struct D_audio_stream *__audio_stream,
                        float                  __gain);

/**
 * \brief Sets whether the given audio stream will loop or not.
 *        NOTE(all): Make sure to set this before playing the
 *        audio stream. Setting after can lead to some weird
 *        behaviours from openAL.
 *
 * \param __audio_stream Specifies the audio stream whose loop
 *                       state will change.
 * \param __loop         Specifies the new loop state.
 */
void
D_set_audio_stream_loop(struct D_audio_stream *__audio_stream,
                        bool                   __loop);

/**
 * \brief Sets the position of an audio stream.
 *        NOTE(all): This changes the local position of THIS
 *        specific audio stream. Depending on the position of
 *        the general audio it may change.
 *
 * \param __audio_stream Specifies the audio stream whose position
 *                       will change.
 * \param __position     Specifies the new position. 
 */
void
D_set_audio_stream_position(struct D_audio_stream *__audio_stream,
                            vec3                   __position);

/**
 * \brief Sets the playback position/offset of an audio stream.
 *        NOTE(all): Make sure to set it while it's playing or paused.
 *        Otherwise, there will be no effect if it's stopped.
 *        NOTE(all): Make sure to know well the audio thes stream is
 *        playing. If you give it an offset out of bounds, you can
 *        expect some weird results (or simply a message error from OpenAL).
 *
 * \param __audio_stream Specifies the audio stream whose playback offset
 *                       will be changed.
 * \param __offset       Specifies the new offset.
 */
void
D_set_audio_stream_offset(struct D_audio_stream *__audio_stream,
                          float                  __offset);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_AUDIO_H__ */
