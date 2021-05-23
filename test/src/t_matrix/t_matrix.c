/**
 * \file test/src/t_matrix/t_matrix.c
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
  struct D_shaders *arrow_shaders = D_create_shaders_from_file("test/src/t_matrix/res/arrow_vertex_shader.glsl",
                                                               "test/src/t_matrix/res/arrow_fragment_shader.glsl");

  f32 arrow_surface[] =
  {
    1.0f,  0.1f, 0.0f, 1.0f, 1.0f,
    1.0f, -0.1f, 0.0f, 1.0f, 0.0f,
    0.0f, -0.1f, 0.0f, 0.0f, 0.0f,
    0.0f,  0.1f, 0.0f, 0.0f, 1.0f
  };
  u32 arrow_surface_indices[] = { 0, 1, 3, 1, 2, 3 };

  struct D_vao *arrow_vao = D_create_vao();
  struct D_vbo *arrow_vbo = D_create_vbo(GL_ARRAY_BUFFER, GL_TRIANGLES, GL_STATIC_DRAW);
  struct D_vbo *arrow_ebo = D_create_vbo(GL_ELEMENT_ARRAY_BUFFER, GL_TRIANGLES, GL_STATIC_DRAW);
  D_bind_vao(arrow_vao);
  D_vbo_data(arrow_vbo, sizeof(arrow_surface), arrow_surface);
  D_vbo_data(arrow_ebo, sizeof(arrow_surface_indices), arrow_surface_indices);

  D_vao_attrib_pointer(arrow_vao, 0, 3, GL_FLOAT, 5 * sizeof(float), 0);
  D_vao_attrib_pointer(arrow_vao, 1, 2, GL_FLOAT, 5 * sizeof(float), 3);

  struct D_texture *arrow_texture = D_create_texture("test/src/t_matrix/res/arrow.png",
                                                     GL_TEXTURE_2D,
                                                     GL_REPEAT, GL_REPEAT,
                                                     GL_LINEAR, GL_LINEAR,
                                                     GL_RGBA,
                                                     true,
                                                     GL_TEXTURE0);

#ifdef __D_DEBUG__
  D_unbind_vao();
#endif /* __D_DEBUG__ */

  D_apply_shaders(arrow_shaders);
  D_set_uniform_i32(arrow_shaders, 0, "u_texture_arrow");

  /* mat */
  mat4 arrow_transform;
  glm_mat4_identity(arrow_transform);
  vec3 arrow_transform_axis = {0.0f, 0.0f, 1.0f};
  glm_rotate(arrow_transform, glm_rad(-90.0f), arrow_transform_axis);

  /* time */
  f64 prev_time, curr_time;

  while (D_is_window_open(window))
  {
    D_clear_window(0.1f, 0.1f, 0.1f, 1.0f);

    curr_time = glfwGetTime();
    if (curr_time - prev_time >= 0.016f)
    {
      glm_rotate(arrow_transform, glm_rad(1.0f), arrow_transform_axis);
      prev_time = curr_time;
    }

    if (glfwGetKey(window->handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    { goto end; }

    D_bind_texture(arrow_texture);
    D_set_uniform_mat4(arrow_shaders, arrow_transform, "u_transform_arrow");
    D_draw_elements(arrow_vao, arrow_ebo, 6, GL_UNSIGNED_INT, arrow_shaders);

    D_swap_window_buffers();
    D_poll_window_events();
  }

end:
  D_end_window(window);
  D_end();

  return 0;
}
