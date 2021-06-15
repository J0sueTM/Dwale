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

  struct D_window *window = D_create_window("Dwale", 800, 600, -1, true, true);
  D_set_window_view((vec2){ 0.0f, 0.0f }, (vec2){ 16.0f, 9.0f }, true);

  struct D_shaders *surface_shaders =
    D_create_shaders_from_file("test/src/t_surface/res/vertex.glsl", "test/src/t_surface/res/fragment.glsl");
  struct D_texture *tux =
    D_create_texture("test/src/t_surface/res/tux.png", GL_TEXTURE_2D,
                     GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR,
                     GL_RGBA, true, GL_TEXTURE0);
  struct D_texture *gnu =
    D_create_texture("test/src/t_surface/res/gnu.png", GL_TEXTURE_2D,
                     GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR,
                     GL_RGBA, true, GL_TEXTURE1);
  struct D_surface *surface =
    D_create_surface(D_SURFACE_RECTANGLE, GL_STATIC_DRAW, -1.0f, -1.0f, -1.0f, 0.4f, -0.2f, 0.4f, -0.2f, -1.0f);
  D_set_surface_shaders(surface, surface_shaders);

  D_push_texture_to_surface(surface, tux, "u_texture_tux");
  D_push_texture_to_surface(surface, gnu, "u_texture_gnu");
  D_prepare_surface_for_rendering(surface);

  struct D_shaders *freebsd_surface_shaders =
    D_create_shaders_from_file("test/src/t_surface/res/vertex.glsl", "test/src/t_surface/res/fragment_bsd.glsl");
  struct D_texture *freebsd =
    D_create_texture("test/src/t_surface/res/freebsd.png", GL_TEXTURE_2D,
                     GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR,
                     GL_RGBA, true, GL_TEXTURE0);
  struct D_surface *freebsd_surface =
    D_create_surface(D_SURFACE_RECTANGLE, GL_STATIC_DRAW, 0.3f, 0.0f, 0.3f, 0.8f, 0.8f, 0.8f, 0.8f, 0.0f);
  D_set_surface_shaders(freebsd_surface, freebsd_surface_shaders);

  D_push_texture_to_surface(freebsd_surface, freebsd, "u_texture_freebsd");
  D_prepare_surface_for_rendering(freebsd_surface);

  while (D_is_window_open(window))
  {
    D_clear_window(0.2f, 0.4f, 0.8f, 1.0f);

    if (glfwGetKey(window->handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      goto end;

    D_bind_textures_from_surface(surface);
    D_draw_surface(surface, NULL);

    D_bind_textures_from_surface(freebsd_surface);
    D_draw_surface(freebsd_surface, NULL);

    D_swap_window_buffers();
    D_poll_window_events();
  }
  
end:
  D_end_surface(surface);
  D_end_texture(tux);
  D_end_texture(gnu);
  D_end_shaders(surface_shaders);
  
  D_end_surface(freebsd_surface);
  D_end_texture(freebsd);
  D_end_shaders(freebsd_surface_shaders);
  
  D_end_window(window);
  D_end();

  return 0;
}
