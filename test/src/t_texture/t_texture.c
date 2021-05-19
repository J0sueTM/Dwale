/**
 * \file test/src/t_texture/t_texture.c
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date May 16, 2021
 *
 * \brief Texture test
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

struct f32vec2 mouse_pos;

static void
_mouse_callback(GLFWwindow *__window,
                f64         __x,
                f64         __y)
{
  mouse_pos.x = (f32)__x;
  mouse_pos.y = (f32)__y;
}

int
main(int    argc,
     char **argv)
{
  D_init();
  struct D_window *window = D_create_window("Dwale", 615, 402, -1, true, false);
  glfwSetCursorPosCallback(window->handle, _mouse_callback);
  struct f32vec2 window_dims =
  {
    (f32)window->current_dimensions.x,
    (f32)window->current_dimensions.y
  };
  f64 previous_elapsed_time = glfwGetTime(), current_elapsed_time;
  u32 frame_count = 0;

  struct D_shaders *shaders = D_create_shaders_from_file("test/src/t_texture/res/vertex_shader.glsl",
                                                         "test/src/t_texture/res/fragment_shader.glsl");

  float vertices_quad[] =
  {
    /* position coords */ /* texture coords */
     0.4f,  0.7f, 0.0f,    1.0f, 1.0f,
     0.4f, -0.7f, 0.0f,    1.0f, 0.0f,
    -0.4f, -0.7f, 0.0f,    0.0f, 0.0f,
    -0.4f,  0.7f, 0.0f,    0.0f, 1.0f
  };
  u32 vertices_quad_indices[] =
  {
    0, 1, 3,
    1, 2, 3
  };
  struct D_vao *__vao_quad = D_create_vao();
  struct D_vbo *__vbo_quad = D_create_vbo(GL_ARRAY_BUFFER, GL_TRIANGLES, GL_STATIC_DRAW);
  struct D_vbo *__ebo_quad = D_create_vbo(GL_ELEMENT_ARRAY_BUFFER, GL_TRIANGLES, GL_STATIC_DRAW);
  D_bind_vao(__vao_quad);
  D_vbo_data(__vbo_quad, sizeof(vertices_quad), vertices_quad);
  D_vbo_data(__ebo_quad, sizeof(vertices_quad_indices), vertices_quad_indices);
  
  D_vao_attrib_pointer(__vao_quad, 0, 3, GL_FLOAT, 5 * sizeof(float), 0);
  D_vao_attrib_pointer(__vao_quad, 1, 2, GL_FLOAT, 5 * sizeof(float), 3);

  struct D_texture *city_texture = D_create_texture("test/src/t_texture/res/city.png",
                                                    GL_TEXTURE_2D,
                                                    GL_REPEAT, GL_REPEAT,
                                                    GL_LINEAR, GL_LINEAR,
                                                    GL_RGBA,
                                                    true,
                                                    GL_TEXTURE0);
  struct D_texture *test_texture = D_create_texture("test/src/t_texture/res/tux.jpg",
                                                    GL_TEXTURE_2D,
                                                    GL_REPEAT, GL_REPEAT,
                                                    GL_LINEAR, GL_LINEAR,
                                                    GL_RGB,
                                                    true,
                                                    GL_TEXTURE1);

#ifdef __D_DEBUG__
  D_unbind_vao(__vao_quad);
#endif /* __D_DEBUG__ */

  D_apply_shaders(shaders);
  D_set_uniform_i32(shaders, 0, "u_texture_city");
  D_set_uniform_i32(shaders, 1, "u_texture_tux");

  while (D_is_window_open(window))
  {
    current_elapsed_time = glfwGetTime();
    ++frame_count;
    if (current_elapsed_time - previous_elapsed_time >= 1.0f)
    {
      printf("%d\n", frame_count);

      frame_count = 0;
      previous_elapsed_time = current_elapsed_time;
    }

    D_clear_window(0.1f, 0.1f, 0.1f, 1.0f);

    if (glfwGetKey(window->handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    { goto end; }

    if (glfwGetKey(window->handle, GLFW_KEY_ENTER) == GLFW_PRESS)
    { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
    else if (glfwGetKey(window->handle, GLFW_KEY_ENTER) == GLFW_RELEASE)
    { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }

    D_bind_texture(test_texture);
    D_set_uniform_f32(shaders, glfwGetTime(), "u_time");
    D_draw_elements(__vao_quad, __ebo_quad, 6, GL_UNSIGNED_INT, shaders);

    D_swap_window_buffers();
    D_poll_window_events();
  }

end:
  D_end_vao(__vao_quad);
  D_end_vbo(__vbo_quad);
  D_end_vbo(__ebo_quad);
  D_end_texture(test_texture);
  D_end_window(window);
  D_end();
}
