/**
 * \file src/dwale.c
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date April 22, 2021
 *
 * \brief Base includes for dwale
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

static struct D_audio *audio;

void
D_init()
{
  D_init_video();
  audio = D_init_audio(audio);
}

void
D_end()
{
  D_end_audio(audio);
  D_end_video();
}
