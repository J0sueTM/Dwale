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
#include "cglm/vec2.h"
#include "cglm/vec4.h"

struct D_window
{
  GLFWwindow  *handle;
  GLFWmonitor *monitor;
  GLFWmonitor **alt_monitors;

  bool fullscreen;
  const GLFWvidmode *fullscreen_dimensions;
  vec2 windowed_dimensions, current_dimensions;

  vec2 view_offset;
  vec2 view_dimensions;
  vec2 view_proportion;
  bool center_view;
};

/**
 * \brief Creates a new window instance out of the global window.
 *        NOTE(all): Do not create another window besides the first,
 *        dwale won't be able to handle it.
 *
 * \param __title           Specifies the window's title.
 * \param __width           Specifies the window's width.
 * \param __height          Specifies the window's height.
 * \param __monitor_index   Specifies the monitor on which the window should be rendered.
 *                          NOTE(all): If negative, the window won't be fullscreen
 *                          and will be rendered on the primary screen.
 * \param __context_current Specifies whether the window will be the current OpenGL rendering
 *                          context or not.
 *                          NOTE(all): This can be toggled after.
 *
 * \return Pointer to the created window.
 */  
struct D_window *
D_create_window(char *__title,
                float __width,
                float __height,
                int   __monitor_index,
                bool  __context_current,
                bool  __resizable);

/**
 * \brief Ends the currently global window instance.
 */  
void
D_end_window();

/**
 * \brief Toggles the currently bounded OpenGL rendering context to the global window instance.
 */
void
D_toggle_context_current();

/**
 * \brief Checks whether the global window instance is open or not.
 *
 * \return Whether the global window instance is open (true) or not (false).
 */  
bool
D_is_window_open();

/**
 * \brief Clears the currently bounded OpenGL rendering context.
 *        NOTE(all): This will only clear the global window if it's the currently
 *                   bounded OpenGL rendering context. Make sure to toggle it.
 *
 * \param __red   Specifies the red channel.
 * \param __green Specifies the green channel.
 * \param __blue  Specifies the blue channel.
 * \param __alpha Specifies the alpha channel.
 */  
void
D_clear_window(float __red,
               float __green,
               float __blue,
               float __alpha);

/**
 * \brief Swaps the window's buffers.
 */  
void
D_swap_window_buffers();

/**
 * \brief Poll window's events.
 */  
void
D_poll_window_events();

/**
 * \brief Sets current window's gl viewport rendering area
 *
 * \param __dimensions Specifies the positions of the area quad.
 *
 * NOTE(all): This functions expects you to give normalised values ranging:
 *            { 0.0f, 0.0f } for the left bottom corner
 *            { 1.0f, 1.0f } for the right top corner
 */
void
D_set_window_view(vec2 __offset,
                  vec2 __proportion,
                  bool __center_view);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_WINDOW_H__ */
