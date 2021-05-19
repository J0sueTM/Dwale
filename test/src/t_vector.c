/**
 * \file test/src/t_vector.c
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date May 18, 2021
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

void
_text();

int
main(int    argc,
     char **argv)
{
  _text();

  D_init();
  struct D_window *window = D_create_window("Dwale", 800, 600, -1, true, false);
  struct D_shaders *arrow_shaders =
    D_create_shaders_from_file("test/src/res_vector/arrow_vertex_shader.glsl",
                               "test/src/res_vector/arrow_fragment_shader.glsl");
  float arrow_quad[] =
  {
     0.4f,  0.2f, 0.0f, 1.0f, 1.0f,
     0.4f, -0.2f, 0.0f, 1.0f, 0.0f,
    -0.2f, -0.2f, 0.0f, 0.0f, 0.0f,
    -0.2f,  0.2f, 0.0f, 0.0f, 1.0f
  };
  u32 arrow_quad_indices[] =
  {
    0, 1, 3,
    1, 2, 3
  };
  struct f32vec2 arrow_pos =
  { .x = 0.8f, .y = 0.2f };

  struct D_vao *arrow_vao = D_create_vao();
  struct D_vbo *arrow_vbo = D_create_vbo(GL_ARRAY_BUFFER, GL_TRIANGLES, GL_STATIC_DRAW);
  struct D_vbo *arrow_ebo = D_create_vbo(GL_ELEMENT_ARRAY_BUFFER, GL_TRIANGLES, GL_STATIC_DRAW);
  D_bind_vao(arrow_vao);
  D_vbo_data(arrow_vbo, sizeof(arrow_quad), arrow_quad);
  D_vbo_data(arrow_ebo, sizeof(arrow_quad_indices), arrow_quad_indices);

  D_vao_attrib_pointer(arrow_vao, 0, 3, GL_FLOAT, 5 * sizeof(float), 0);
  D_vao_attrib_pointer(arrow_vao, 1, 2, GL_FLOAT, 5 * sizeof(float), 3);

  struct D_texture *arrow_texture =
    D_create_texture("test/src/res_vector/arrow.png",
                     GL_TEXTURE_2D,
                     GL_REPEAT, GL_REPEAT,
                     GL_LINEAR, GL_LINEAR,
                     GL_RGBA,
                     true,
                     GL_TEXTURE0);

#ifdef __D_DEBUG_
  D_unbind_vao();
#endif /* __D_DEBUG__ */

  D_apply_shaders(arrow_shaders);
  D_set_uniform_i32(arrow_shaders, 0, "u_texture_arrow");

  while (D_is_window_open(window))
  {
    D_clear_window(0.1f, 0.1f, 0.1f, 1.0f);

    if (glfwGetKey(window->handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    { goto end; }

    if (glfwGetKey(window->handle, GLFW_KEY_ENTER) == GLFW_PRESS)
    { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
    else if (glfwGetKey(window->handle, GLFW_KEY_ENTER) == GLFW_RELEASE)
    { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }

    /* logic */
    D_rotate_vector(f32, &arrow_pos, 0.1f);

    /* render */
    D_bind_texture(arrow_texture);
    D_set_uniform_f32vec2(arrow_shaders, arrow_pos, "u_pos");
    D_draw_elements(arrow_vao, arrow_ebo, 6, GL_UNSIGNED_INT, arrow_shaders);

    D_swap_window_buffers();
    D_poll_window_events();
  }

end:
  D_end_vao(arrow_vao);
  D_end_vbo(arrow_vbo);
  D_end_vbo(arrow_ebo);
  D_end_window(window);
  D_end();

  return 0;
}

void
_text()
{
  struct f32vec2 test_vector1 =
  { .x = 20.43f, .y = 0.6f };
  struct f32vec2 test_vector2 =
  { .x = 10.0f, .y = 2.4f };
  struct f32vec2 test_vector3;
  struct f32vec4 test_vector4 =
  { .x = 43.1f, .y = 33.9f, .z = 32.44f, .w = 102.48f };
  struct f32vec4 test_vector5 =
  { .x = 3.4f, .y = 968.8f, .z = 865.2f, .w = 0.4f };
  struct f32vec4 test_vector6;

  /* add */
  D_add_vector_to(&test_vector1, &test_vector2, &test_vector3);
  printf("Expects 30.43 : 3.00\nGot     %.2f : %.2f\n", test_vector3.x, test_vector3.y);

  test_vector1.x = 0.4f;
  test_vector1.y = 0.94f;
  D_add_vector(&test_vector1, &test_vector2);
  printf("\nExpects 10.40 : 3.34\nGot     %.2f : %.2f\n", test_vector1.x, test_vector1.y);

  D_add_vector_to(&test_vector4, &test_vector5, &test_vector6);
  printf("\nExpects 46.50 : 1002.70 : 897.64 : 102.88\nGot     %.2f : %.2f : %.2f : %.2f\n", test_vector6.x,
                                                                                             test_vector6.y,
                                                                                             test_vector6.z,
                                                                                             test_vector6.w);

  /* sub */
  D_sub_vector(&test_vector3, &test_vector1);
  printf("\nExpects 20.03 : -0.34\nGot     %.2f : %.2f\n", test_vector3.x, test_vector3.y);

  D_sub_vector_to(&test_vector4, &test_vector1, &test_vector3);
  printf("\nExpects 32.70 : 30.56\nGot     %.2f : %.2f\n", test_vector3.x, test_vector3.y);

  /* mult */
  test_vector1.x = 2.0f;
  test_vector2.x = 9.4f;
  test_vector1.y = 3.0f;
  test_vector2.y = 4.2f;
  D_mult_vector(&test_vector1, &test_vector2);
  printf("\nExpects 18.80 : 12.60\nGot     %.2f : %.2f\n", test_vector1.x, test_vector1.y);

  test_vector1.x = 2.0f;
  test_vector2.x = 9.4f;
  D_mult_vector_to(&test_vector1, &test_vector2, &test_vector3);
  printf("\nExpects 18.80 : 52.92\nGot     %.2f : %.2f\n", test_vector3.x, test_vector3.y);

  /* div */
  test_vector1.x = 8.2f;
  test_vector2.x = 4.1f;
  test_vector1.y = 9.3f;
  test_vector2.y = 3.1f;
  D_div_vector(&test_vector1, &test_vector2);
  printf("\nExpects 2.00 : 3.00\nGot     %.2f : %.2f\n\n", test_vector1.x, test_vector1.y);

  test_vector2.x = 0.0f;
  test_vector2.y = 0.0f;
  D_div_vector_to(&test_vector1, &test_vector2, &test_vector3);
  printf("\nExpects 18.80 : 52.92\nGot     %.2f : %.2f\n", test_vector3.x, test_vector3.y);

  test_vector3.x = 3;
  test_vector3.y = 4;
  printf("\n%.2f\n", D_rotation_vector(&test_vector3));

  for (i32 i = 0; i < 10; ++i)
  {
    D_rotate_vector(f32, &test_vector3, 0.1);

    printf("%.2f\n", D_rotation_vector(&test_vector3));
    printf("%.2f : %.2f\n", test_vector3.x, test_vector3.y);
  }
}
