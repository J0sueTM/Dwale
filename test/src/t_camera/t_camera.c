/**
 * \file test/src/t_camera/t_camera.c
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date June 01, 2021
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
  struct D_camera *camera = D_create_camera(window, -0.1f, 100.0f);

  struct D_shaders *tux_shaders =
    D_create_shaders(D_VERTEX_SHADER_ALL_LAYOUTS_PRECALCULATED_MVP, D_FRAGMENT_SHADER_ALL_LAYOUTS_PRECALCULATED_MVP("u_texture_tux"));
  struct D_texture *tux_texture =
    D_create_texture("test/src/t_camera/res/tux.png", GL_TEXTURE_2D,
                     GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR,
                     GL_RGBA, true, GL_TEXTURE0);
  struct D_surface *tux_surface =
    D_create_surface(D_SURFACE_RECTANGLE, GL_STATIC_DRAW, -0.7f, -0.8f, -0.7f, 0.8f, 0.7f, 0.8f, 0.7f, -0.8f);
  D_set_surface_shaders(tux_surface, tux_shaders);

  D_push_texture_to_surface(tux_surface, tux_texture, "u_texture_tux");
  D_prepare_surface_for_rendering(tux_surface);

  vec3 velocity = { 0.0f, 0.0f, 0.0f };
  float rotation = 0.0f;
  while (D_is_window_open(window))
  {
    D_clear_window(0.2f, 0.2f, 0.2f, 1.0f);

    if (glfwGetKey(window->handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      D_close_window(window);

    if (glfwGetKey(window->handle, GLFW_KEY_LEFT) == GLFW_PRESS &&
        glfwGetKey(window->handle, GLFW_KEY_SPACE) == GLFW_PRESS)
      rotation += 1.0f;
    else if (glfwGetKey(window->handle, GLFW_KEY_LEFT) == GLFW_PRESS)
      velocity[0] -= 0.05f;

    if (glfwGetKey(window->handle, GLFW_KEY_RIGHT) == GLFW_PRESS &&
        glfwGetKey(window->handle, GLFW_KEY_SPACE) == GLFW_PRESS)
      rotation -= 1.0f;
    else if (glfwGetKey(window->handle, GLFW_KEY_RIGHT) == GLFW_PRESS)
      velocity[0] += 0.05f;

    if (glfwGetKey(window->handle, GLFW_KEY_UP) == GLFW_PRESS)
      velocity[1] += 0.05;
    if (glfwGetKey(window->handle, GLFW_KEY_DOWN) == GLFW_PRESS)
      velocity[1] -= 0.05f;

    D_bind_textures_from_surface(tux_surface);
    D_reset_camera(camera);
    glm_translate(tux_surface->model, velocity);
    glm_rotate(tux_surface->model, glm_rad(rotation), (vec3){ 0.0f, 0.0f, 1.0f });
    D_draw_surface(tux_surface, camera);

    D_swap_window_buffers();
    D_poll_window_events();
  }

  D_end_texture(tux_texture);
  D_end_surface(tux_surface);
  D_end_shaders(tux_shaders);
  D_end_camera(camera);
  D_end_window(window);
  D_end();

  return 0;
}
