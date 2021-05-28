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
_update_current_dimensions()
{
  if (_global_window->fullscreen)
  {
    _global_window->current_dimensions[0] = (float)_global_window->fullscreen_dimensions->width;
    _global_window->current_dimensions[1] = (float)_global_window->fullscreen_dimensions->height;
  }
  else
  {
    glm_vec2_copy(_global_window->windowed_dimensions, _global_window->current_dimensions);
  }

  /*
   * Calculates the view's height depending on the proportion. Based on the result, we can define whether the view will be
   * be attached to the bottom of the window or the left.
   *
   * In case the calculated height is bigger than the actual window size, it should be attached to the left and the width should
   * be calculated instead of the height, and the opposite otherwise.
   *
   * NOTE(all): Since this will only show on the screen on rendering step, you
   * still can change the view with D_set_window_view()
   * Just be aware of some weird results if you do this during rendering.
   */
  float temp_view_height = (_global_window->current_dimensions[0] * _global_window->view_proportion[1]) / _global_window->view_proportion[0];
  if (temp_view_height > _global_window->current_dimensions[1])
  {
    _global_window->view_dimensions[0] =
      ((_global_window->current_dimensions[1] * _global_window->view_proportion[0]) / _global_window->view_proportion[1]) - _global_window->view_offset[0];
    _global_window->view_dimensions[1] = _global_window->current_dimensions[1] - _global_window->view_offset[1];
  }
  else
  {
    _global_window->view_dimensions[0] = _global_window->current_dimensions[0] - _global_window->view_offset[0];
    _global_window->view_dimensions[1] = temp_view_height - _global_window->view_offset[1];
  }

  if (_global_window->center_view)
  {
    glViewport((_global_window->current_dimensions[0] * 0.5f) - (_global_window->view_dimensions[0] * 0.5f) + _global_window->view_offset[0],
               (_global_window->current_dimensions[1] * 0.5f) - (_global_window->view_dimensions[1] * 0.5f) + _global_window->view_offset[1],
               _global_window->view_dimensions[0], _global_window->view_dimensions[1]);
  }
  else
  {
    glViewport(_global_window->view_offset[0], _global_window->view_offset[1],
               _global_window->view_dimensions[0], _global_window->view_dimensions[1]);
  }
}

static void
_default_framebuffer_size_callback(GLFWwindow *__window,
                                   int         __width,
                                   int         __height)
{
  _global_window->windowed_dimensions[0] = (float)__width;
  _global_window->windowed_dimensions[1] = (float)__height;

  _update_current_dimensions();
}

static void
_default_error_callback(int         __code,
                        const char *__description)
{
  D_raise_error((char *)__description);
}

struct D_window *
D_create_window(char  *__title,
                float  __width,
                float  __height,
                int    __monitor_index,
                bool   __context_current,
                bool   __resizable)
{
  if (!__title)
  {
    D_raise_error(DERR_NOPARAM("__title", "Title can't be NULL"));
    
    return NULL;
  }
  else if (__width  <= 0.0f ||
           __height <= 0.0f)
  {
    D_raise_error(DERR_NOPARAM("__width || __height", "Window size can't be less than 0"));

    return NULL;
  }

  _global_window = (struct D_window *)malloc(sizeof(struct D_window));
  D_assert_fatal(_global_window, NULL);
  
  _global_window->windowed_dimensions[0] = __width;
  _global_window->windowed_dimensions[1] = __height;

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

    glfwWindowHint(GLFW_RESIZABLE, __resizable);

    goto normal_window_selected;
  }
  else
  {
    int *monitor_count = (int *)malloc(sizeof(int)), final_monitor;
    _global_window->alt_monitors = glfwGetMonitors(monitor_count);

    final_monitor = (__monitor_index >= *monitor_count) ? 0 : __monitor_index;
    _global_window->monitor = *(_global_window->alt_monitors + final_monitor);
    _global_window->fullscreen_dimensions = glfwGetVideoMode(_global_window->monitor);

    _global_window->handle =
      glfwCreateWindow(_global_window->fullscreen_dimensions->width, _global_window->fullscreen_dimensions->height, __title, _global_window->monitor, NULL);
    _global_window->fullscreen = true;

    free(monitor_count);
    goto end_window_creation;
  }

normal_window_selected:
  _global_window->handle =
    glfwCreateWindow(_global_window->windowed_dimensions[0], _global_window->windowed_dimensions[1], __title, _global_window->monitor, NULL);
  
end_window_creation:
  if (__context_current)
  { 
    D_toggle_context_current(_global_window);
    glfwSetFramebufferSizeCallback(_global_window->handle, _default_framebuffer_size_callback);
  }

  D_set_window_view((vec2){ 0.0f, 0.0f }, (vec2){ 1.0f, 1.0f }, true);

  D_raise_log("Created window");
  return _global_window;
}

void
D_end_window()
{
  if (!_global_window)
    return;

  glfwDestroyWindow(_global_window->handle);
  D_raise_log("Ended window");
}

void
D_toggle_context_current()
{
  if (!_global_window)
  {
    D_raise_error(DERR_NOPARAM("_global_window", "Global window can't be NULL. Check if you created it"));

    return;
  }

  glfwMakeContextCurrent(_global_window->handle);

#ifndef __D_INIT_VIDEO_GLAD__
#define __D_INIT_VIDEO_GLAD__
  D_assert_fatal(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), DERR_NOINIT("glad"));
#endif /* __D_INIT_VIDEO_GLAD__ */

  D_post_init_video();
}

bool
D_is_window_open(struct D_window *_global_window)
{
  return !glfwWindowShouldClose(_global_window->handle);
}

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
{
  glfwSwapBuffers(_global_window->handle);
}

void
D_poll_window_events()
{
  glfwPollEvents();
}

void
D_set_window_view(vec2 __offset,
                  vec2 __proportion,
                  bool __center_view)
{
  if (!_global_window)
    return;

  glm_vec2_copy(__offset, _global_window->view_offset);
  glm_vec2_copy(__proportion, _global_window->view_proportion);
  _global_window->center_view = __center_view;
  
  _update_current_dimensions();
}
