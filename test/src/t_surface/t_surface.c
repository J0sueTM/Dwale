/**
 * \file test/src/t_surface/t_surface.c
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date May 21, 2021
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

  struct D_window *window = D_create_window("Dwale", 800, 600, -1, true, false);
  struct D_shaders *surface_shaders = D_create_shaders_from_file("test/src/t_surface/res/vertex.glsl", "test/src/t_surface/res/fragment.glsl");

  f32 surface_vertices[] =
  {
     0.6f,  0.4f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
     0.6f, -0.4f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.6f, -0.4f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.6f, -0.4f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
  };
  u32 surface_indices[] = { 0, 1, 3, 1, 2, 3 };
  struct D_texture *tux = D_create_texture("test/src/t_surface/res/tux.png", GL_TEXTURE_2D, GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGBA, true, GL_TEXTURE0);
  struct D_texture *gnu = D_create_texture("test/src/t_surface/res/gnu.png", GL_TEXTURE_2D, GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGBA, true, GL_TEXTURE1);
  
  struct D_surface *surface = D_create_surface(surface_vertices, surface_indices, GL_TRIANGLES, GL_STATIC_DRAW, 6, GL_UNSIGNED_INT, surface_shaders);
  D_push_texture_to_surface(surface, tux, "u_texture_tux");
  D_push_texture_to_surface(surface, gnu, "u_texture_gnu");
  D_prepare_surface_for_rendering(surface);

  while (D_is_window_open(window))
  {
    D_clear_window(0.1f, 0.1f, 0.1f, 1.0f);

    if (glfwGetKey(window->handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    { goto end; }

    D_bind_textures_from_surface(surface);
    D_draw_surface(surface);

    D_swap_window_buffers();
    D_poll_window_events();
  }
  
end:
  D_end_surface(surface);
  D_end_window(window);
  D_end();

  return 0;
}
