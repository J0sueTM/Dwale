/**
 * \file test/src/t_audio.c
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date July 20, 2021
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

#include "dwale.h"

struct D_audio *audio;

int
main()
{
  D_init();

  struct D_audio_stream *test_audio_stream = D_create_audio_stream("test/src/t_audio/res/test_music.ogg");
  D_end_audio_stream(test_audio_stream);
  
  D_end();
  
  return 0;
}
