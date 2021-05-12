/**
 * \file test/src/t_gl_object.c
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date April 30, 2021
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

const char *vertex_shader_source =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragment_shader_source =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

u32 fragment_shader, vertex_shader, shader_program;

bool
_shader();

int
main(int    argc,
     char **argv)
{
  D_init();
  struct D_window *window = D_create_window("Dwale", 800, 600, -1, true);

  struct D_shaders *test_shaders = D_create_shaders(vertex_shader_source, fragment_shader_source);

  /* triangle */
  float vertices[] =
  {
    -0.8f, -0.1f, 0.0f,
    -0.2f,  0.0f, 0.0f,
     0.0f,  0.5f, 0.0f
  };
  struct D_vao *__test_vao = D_create_vao();  
  struct D_vbo *__test_vbo = D_create_vbo(GL_ARRAY_BUFFER, GL_TRIANGLES, GL_STATIC_DRAW);
  D_bind_vao(__test_vao);
  D_vbo_data(__test_vbo, sizeof(vertices), vertices);
  D_vao_attrib_pointer(__test_vao, 0, 3, GL_FLOAT, 3 * sizeof(float), 0);
  D_unbind_vbo();
  D_unbind_vao();

  /* quad */
  float vertices_quad[] =
  {
    0.8f,  0.8f, 0.0f,
    0.8f, -0.6f, 0.0f,
    0.2f, -0.1f, 0.0f,
    0.1f,  0.2f, 0.0f
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
  /* vbo */
  D_vbo_data(__vbo_quad, sizeof(vertices_quad), vertices_quad);
  /* ebo */
  D_vbo_data(__ebo_quad, sizeof(vertices_quad_indices), vertices_quad_indices);
  D_vao_attrib_pointer(__vao_quad, 0, 3, GL_FLOAT, 3 * sizeof(float), 0);
  D_unbind_vao(__vao_quad);

  while (D_is_window_open(window))
  {
    D_clear_window(0.2f, 0.4f, 0.1f, 1.0f);

    if (glfwGetKey(window->handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    { goto end_all; }
    else if (glfwGetKey(window->handle, GLFW_KEY_F11) == GLFW_PRESS)
    {  }

    if (glfwGetKey(window->handle, GLFW_KEY_ENTER) == GLFW_PRESS)
    { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
    else if (glfwGetKey(window->handle, GLFW_KEY_ENTER) == GLFW_RELEASE)
    { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }

    D_apply_shaders(test_shaders);

    D_bind_vao(__test_vao);
    glDrawArrays(__test_vbo->draw_type, 0, 3);
    D_unbind_vao();

    D_bind_vao(__vao_quad);
    glDrawElements(__ebo_quad->draw_type, 6, GL_UNSIGNED_INT, 0);
    D_unbind_vao();
    
    D_swap_window_buffers();
    D_poll_window_events();
  }

end_all:  
  /* tringle */
  D_end_vao(__test_vao);
  D_end_vbo(__test_vbo);

  /* quad */
  D_end_vao(__vao_quad);
  D_end_vbo(__vbo_quad);
  D_end_vbo(__ebo_quad);

  glDeleteProgram(shader_program);

  D_end_window(window);
  D_end();

  return 0;
}
