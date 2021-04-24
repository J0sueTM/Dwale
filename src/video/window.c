/**
 * \file src/video/window.c
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

#include "video/window.h"

static void
_update_current_global_dimensions(struct D_window *__window)
{
  if (__window->fullscreen)
  {
    __window->current_global_dimensions.u32vector2.x = __window->fullscreen_dimensions->width;
    __window->current_global_dimensions.u32vector2.y = __window->fullscreen_dimensions->height;
  }
  else
  {
    __window->current_global_dimensions.u32vector2.x = __window->windowed_dimensions.u32vector2.x;
    __window->current_global_dimensions.u32vector2.y = __window->windowed_dimensions.u32vector2.y;
  }
}

static void
_default_framebuffer_size_callback(GLFWwindow *__window,
                                   u32         __width,
                                   u32         __height)
{ glViewport(0, 0, __width, __height); }

struct D_window *
D_create_window(char *__title,
                u32   __width,
                u32   __height,
                i32   __monitor_index,
                bool  __context_current)
{
  if (!__title)
  {
    D_raise_error(DERR_NOPARAM("__title", "Title can't be NULL"));
    
    return NULL;
  }
  else if (!__width)
  {
    D_raise_error(DERR_NOPARAM("__width", "Width can't be NULL"));

    return NULL;
  }
  else if (!__height)
  {
    D_raise_error(DERR_NOPARAM("__height", "Height can't be NULL"));

    return NULL;
  }

  struct D_window *new_window = (struct D_window *)malloc(sizeof(struct D_window));
  D_assert(new_window, NULL);

  new_window->windowed_dimensions.u32vector2.x = __width;
  new_window->windowed_dimensions.u32vector2.y = __height;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /*
   * Gets monitor handle according to __monitor_index
   *
   * If out of bound, the primary monitor will be selected
   * If negative, no monitor will be selected
   */
  if (__monitor_index < 0)
  {
    new_window->monitor = NULL;
    new_window->fullscreen = false;

    goto normal_window_selected;
  }
  else
  {
    i32 *monitor_count = (i32 *)malloc(sizeof(i32)), real_monitor_index;
    new_window->alt_monitors = glfwGetMonitors(monitor_count);

    if (__monitor_index >= *monitor_count)
    { real_monitor_index = 0; }
    else
    { real_monitor_index = __monitor_index; }

    new_window->monitor = *(new_window->alt_monitors + real_monitor_index);
    new_window->fullscreen_dimensions = glfwGetVideoMode(new_window->monitor);

    new_window->handle = glfwCreateWindow(new_window->fullscreen_dimensions->width,
                                          new_window->fullscreen_dimensions->height,
                                          __title,
                                          new_window->monitor,
                                          NULL);
    new_window->fullscreen = true;

    free(monitor_count);
    goto end_window_creation;
  }

normal_window_selected:
  new_window->handle = glfwCreateWindow(new_window->windowed_dimensions.u32vector2.x,
                                        new_window->windowed_dimensions.u32vector2.y,
                                        __title,
                                        new_window->monitor,
                                        NULL);
end_window_creation:
  if (__context_current)
  { D_toggle_context_current(new_window); }

  D_raise_log("Created window");
  return new_window;
}

void
D_end_window(struct D_window *__window)
{
  if (!__window)
  { return; }

  glfwDestroyWindow(__window->handle);
  D_raise_log("Ended window");
}

void
D_toggle_context_current(struct D_window *__window)
{
  if (!__window)
  {
    D_raise_error(DERR_NULLPARAM("__window"));

    return;
  }

  _update_current_global_dimensions(__window);
  glfwMakeContextCurrent(__window->handle);

#ifndef __D_INIT_VIDEO_GLAD__
#define __D_INIT_VIDEO_GLAD__
  D_assert_fatal(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), DERR_NOINIT("glad"));
#endif /* __D_INIT_VIDEO_GLAD__ */
  
  glViewport(0, 0,
             __window->current_global_dimensions.u32vector2.x,
             __window->current_global_dimensions.u32vector2.y);

  D_raise_log("Toggled current OpenGL rendering context");
}

bool
D_is_window_open(struct D_window *__window)
{ return !glfwWindowShouldClose(__window->handle); }
