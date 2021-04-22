/**
 * \file src/video/video.c
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date April 22, 2021
 *
 * \brief Visual related utilities
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

#include "video/video.h"

void
D_init_video()
{
#ifndef __D_INIT_VIDEO__
#define __D_INIT_VIDEO__
  D_assert(glfwInit(), DERR_NOINIT("glfw"));
#endif /* __D_INIT_VIDEO__ */
}

void
D_end_video()
{
#ifdef __D_INIT_VIDEO__
  glfwTerminate();
#endif /* __D_INIT_VIDEO__ */
}
