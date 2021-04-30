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

static struct D_window *_global_window;

static void
_update_current_global_dimensions()
{
  if (_global_window->fullscreen)
  {
    _global_window->current_global_dimensions.u32vector2.x = _global_window->fullscreen_dimensions->width;
    _global_window->current_global_dimensions.u32vector2.y = _global_window->fullscreen_dimensions->height;
  }
  else
  {
    _global_window->current_global_dimensions.u32vector2.x = _global_window->windowed_dimensions.u32vector2.x;
    _global_window->current_global_dimensions.u32vector2.y = _global_window->windowed_dimensions.u32vector2.y;
  }

  glViewport(0, 0,
             _global_window->current_global_dimensions.u32vector2.x,
             _global_window->current_global_dimensions.u32vector2.y);

}

static void
_default_framebuffer_size_callback(GLFWwindow *__window,
                                   i32         __width,
                                   i32         __height)
{ _update_current_global_dimensions(); }

static void
_default_error_callback(i32         __code,
                        const char *__description)
{ D_raise_error((char *)__description); }

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

  _global_window = (struct D_window *)malloc(sizeof(struct D_window));
  D_assert_fatal(_global_window, NULL);

  _global_window->windowed_dimensions.u32vector2.x = __width;
  _global_window->windowed_dimensions.u32vector2.y = __height;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_TRUE);

  glfwSetErrorCallback(_default_error_callback);

  /*
   * Gets monitor handle according to __monitor_index
   *
   * If out of bound, the primary monitor will be selected
   * If negative, no monitor will be selected
   */
  if (__monitor_index < 0)
  {
    _global_window->monitor = NULL;
    _global_window->fullscreen = false;

    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    goto normal_window_selected;
  }
  else
  {
    i32 *monitor_count = (i32 *)malloc(sizeof(i32)), real_monitor_index;
    _global_window->alt_monitors = glfwGetMonitors(monitor_count);

    if (__monitor_index >= *monitor_count)
    { real_monitor_index = 0; }
    else
    { real_monitor_index = __monitor_index; }

    _global_window->monitor = *(_global_window->alt_monitors + real_monitor_index);
    _global_window->fullscreen_dimensions = glfwGetVideoMode(_global_window->monitor);

    _global_window->handle = glfwCreateWindow(_global_window->fullscreen_dimensions->width,
                                              _global_window->fullscreen_dimensions->height,
                                              __title,
                                              _global_window->monitor,
                                              NULL);
    _global_window->fullscreen = true;

    free(monitor_count);
    goto end_window_creation;
  }

normal_window_selected:
  _global_window->handle = glfwCreateWindow(_global_window->windowed_dimensions.u32vector2.x,
                                            _global_window->windowed_dimensions.u32vector2.y,
                                            __title,
                                            _global_window->monitor,
                                            NULL);
end_window_creation:
  if (__context_current)
  { 
    D_toggle_context_current(_global_window);
    glfwSetFramebufferSizeCallback(_global_window->handle, _default_framebuffer_size_callback);
  }

  D_raise_log("Created window");
  return _global_window;
}

void
D_end_window()
{
  if (!_global_window)
  { return; }

  glfwDestroyWindow(_global_window->handle);
  D_raise_log("Ended window");
}

void
D_toggle_context_current()
{
  if (!_global_window)
  {
    D_raise_error(DERR_NULLPARAM("_global_window"));

    return;
  }

  glfwMakeContextCurrent(_global_window->handle);

#ifndef __D_INIT_VIDEO_GLAD__
#define __D_INIT_VIDEO_GLAD__
  D_assert_fatal(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), DERR_NOINIT("glad"));
#endif /* __D_INIT_VIDEO_GLAD__ */

  _update_current_global_dimensions();

  D_raise_log("Toggled current OpenGL rendering context");
}

bool
D_is_window_open(struct D_window *_global_window)
{ return !glfwWindowShouldClose(_global_window->handle); }

void
D_clear_window(float __red,
               float __green,
               float __blue,
               float __alpha)
{
  glClearColor(__red, __green, __blue, __alpha);
  glClear(GL_COLOR_BUFFER_BIT);
}

void
D_swap_window_buffers()
{ glfwSwapBuffers(_global_window->handle); }
