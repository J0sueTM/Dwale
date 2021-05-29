/**
 * \file test/src/t_shaders.c
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date May 29, 2021
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

int
main(int    argc,
     char **argv)
{
  D_init();

  struct D_window *window = D_create_window("Dwale", 800, 600, -1, true, true);
  D_set_window_view((vec2){ 0.0f, 0.0f }, (vec2){ 16.0f, 9.0f }, true);

  struct D_shaders *shaders = D_create_shaders(D_vertex_simple_layouts, D_fragment_simple_layouts);
  float surface_vertices[] =
  {
     1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f
  };
  unsigned int surface_indices[] = { 0, 1, 3, 1, 2, 3 };
  struct D_surface *surface =
    D_create_surface(sizeof(surface_vertices), surface_vertices,
                     sizeof(surface_indices), surface_indices,
                     8, GL_TRIANGLES, GL_STATIC_DRAW,
                     6, GL_UNSIGNED_INT, shaders);

  while (D_is_window_open(window))
  {
    D_clear_window(0.6f, 0.6f, 0.6f, 1.0f);
    
    if (glfwGetKey(window->handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      D_close_window();

    D_draw_surface(surface);

    D_swap_window_buffers();
    D_poll_window_events();
  }

  D_end_surface(surface);
  D_end_shaders(shaders);
  D_end_window(window);
  D_end();

  return 0;
}
