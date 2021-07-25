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
  struct D_camera *camera = D_create_camera(window, -1.0f, 1.0f);

  struct D_shaders *tux_shaders =
    D_create_shaders_from_file("test/src/t_camera/res/tux_vertex.glsl", "test/src/t_camera/res/tux_fragment.glsl");
  struct D_texture *tux_texture =
    D_create_texture("test/src/t_camera/res/tux_tiles.png", GL_TEXTURE_2D,
                     GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR,
                     GL_RGBA, true, GL_TEXTURE0);
  struct D_surface *tux_surface =
    D_create_rectangle_surface(GL_STATIC_DRAW, (vec2){ -0.7f, -0.8f }, (vec2){ -0.7f, 0.8f },
                                               (vec2){ 0.7f, 0.8f }, (vec2){ 0.7f, -0.8f },
                                               3, 9);

  int animation_frame = 0;
  int animation_choice = 0;
  double last_frame, current_frame;
  last_frame = glfwGetTime();
  bool key_pressed = false;

  D_set_surface_shaders(tux_surface, tux_shaders);
  D_push_texture_to_surface(tux_surface, tux_texture, "u_texture_tux");
  D_prepare_surface_for_rendering(tux_surface);

  while (D_is_window_open(window))
  {
    current_frame = glfwGetTime();
    D_clear_window(0.2f, 0.2f, 0.2f, 1.0f);

    if (glfwGetKey(window->handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      D_close_window(window);
    if (glfwGetKey(window->handle, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
      if (glfwGetKey(window->handle, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        D_rotate_surface(tux_surface, glm_rad(-2.0f));
      else if (glfwGetKey(window->handle, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        D_translate_camera(camera, (vec2){ -0.1f, 0.0f });
      else
        D_translate_surface(tux_surface, (vec2){ -0.05f, 0.0f });
    }
    if (glfwGetKey(window->handle, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
      if (glfwGetKey(window->handle, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        D_rotate_surface(tux_surface, glm_rad(2.0f));
      else if (glfwGetKey(window->handle, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        D_translate_camera(camera, (vec2){ 0.1f, 0.0f });
      else
        D_translate_surface(tux_surface, (vec2){ 0.05f, 0.0f });
    }
    if (glfwGetKey(window->handle, GLFW_KEY_UP) == GLFW_PRESS)
    {
      if (glfwGetKey(window->handle, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        D_set_surface_scale(tux_surface, (vec2){ 1.0f, tux_surface->scale[1] + 0.08f });
      else if (glfwGetKey(window->handle, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        D_rotate_camera(camera, glm_rad(2.0f));
      else if (glfwGetKey(window->handle, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        D_set_camera_scale(camera, (vec2){ camera->scale[0], camera->scale[1] + 0.1f });
      else
        D_translate_surface(tux_surface, (vec2){ 0.0f, 0.05f });
    }
    if (glfwGetKey(window->handle, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
      if (glfwGetKey(window->handle, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        D_set_surface_scale(tux_surface, (vec2){ 1.0f, tux_surface->scale[1] - 0.08f });
      else if (glfwGetKey(window->handle, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        D_rotate_camera(camera, glm_rad(-2.0f));
      else if (glfwGetKey(window->handle, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        D_set_camera_scale(camera, (vec2){ camera->scale[0] + 0.1f, camera->scale[1] });
      else
        D_translate_surface(tux_surface, (vec2){ 0.0f, -0.05f });
    }

    if (glfwGetKey(window->handle, GLFW_KEY_SPACE) == GLFW_PRESS && !key_pressed)
    {
      if (animation_choice <= 7)
        ++animation_choice;
      else
        animation_choice = 0;

      key_pressed = true;
    }
    if (glfwGetKey(window->handle, GLFW_KEY_SPACE) == GLFW_RELEASE && key_pressed)
      key_pressed = false;

    D_set_surface_uv_shift(tux_surface, animation_frame, animation_choice, (vec2){ 0.0f, 0.0f });
    D_bind_textures_from_surface(tux_surface);
    D_draw_surface(tux_surface, camera);
    if (current_frame - last_frame >= 0.12f)
    {
      if (animation_frame <= 1)
        ++animation_frame;
      else
        animation_frame = 0;

      last_frame = current_frame;
    }

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
