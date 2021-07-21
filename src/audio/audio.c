/**
 * \file src/audio/audio.c
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date July 21, 2021
 *
 * Copyright (C) Josué Teodoro Moreira
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

static ALCdevice *global_device;

void
D_init_audio()
{
  global_device = alcOpenDevice(NULL);
  D_assert_return_void(global_device, DERR_NOINIT("OpenAL"));
}

void
D_end_audio()
{
  alcCloseDevice(global_device);
}

bool
check_alc_errors()
{
  ALCenum err = alcGetError(global_device);
  if (err != ALC_NO_ERROR)
  {
    switch (err)
    {
    case ALC_INVALID_VALUE:
      D_raise_error("OpenAL: An invalid value was passed to an OpenAL function");
      
      break;
    case ALC_INVALID_DEVICE:
      D_raise_error("OpenAL: A bad device was passed to an OpenAL function");
      
      break;
    case ALC_INVALID_CONTEXT:
      D_raise_error("OpenAL: A bad context was pased to an OpenAL function");
      
      break;
    case ALC_INVALID_ENUM:
      D_raise_error("OpenAL: An unknown enum enum was passed to an OpenAL function");
      
      break;
    case ALC_OUT_OF_MEMORY:
      D_raise_error("OpenAL: Out of memory");
      
      break;
    default:
      D_raise_error("OpenAL: Something went wrong");

      break;
    }

    return false;
  }

  return true;
}
