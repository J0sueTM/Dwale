/**
 * \file inc/video/window.h
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date April 23, 2021
 *
 * \brief Window related functionalities
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

#ifndef __D_WINDOW_H__
#define __D_WINDOW_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "core/core.h"
#include "video/video.h"
#include "util/vector2.h"

struct D_window
{
  GLFWwindow *handle;
  GLFWmonitor *monitor;
  GLFWmonitor **alt_monitors;

  bool fullscreen;
  const GLFWvidmode *fullscreen_dimensions;
  union D_vector2 windowed_dimensions,
                  current_global_dimensions;
};

struct D_window *
D_create_window(char *__title,
                u32   __width,
                u32   __height,
                i32   __monitor_index,
                bool  __context_current);

void
D_end_window();

void
D_toggle_context_current();

bool
D_is_window_open();

void
D_clear_window(float __red,
               float __green,
               float __blue,
               float __alpha);

void
D_swap_window_buffers();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_WINDOW_H__ */
