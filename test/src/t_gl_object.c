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

  if (!_shader())
  {
    D_raise_error("Could not compile shader");

    return -1;
  }

  float vertices[] =
  {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };

  struct D_vao *__test_vao = D_create_vao();  
  struct D_vbo *__test_vbo = D_create_vbo(GL_ARRAY_BUFFER, GL_TRIANGLES, GL_STATIC_DRAW);
  D_bind_vao(__test_vao);
  D_bind_vbo(__test_vbo);

  D_vbo_data(__test_vbo, sizeof(vertices), vertices);
  D_vao_attrib_pointer(__test_vao, __test_vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), 0);

  D_unbind_vbo();
  D_unbind_vao();

  while (D_is_window_open(window))
  {
    D_clear_window(0.2f, 0.4f, 0.1f, 1.0f);

    if (glfwGetKey(window->handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    { goto end_all; }

    glUseProgram(shader_program);
    D_bind_vao(__test_vao);
    glDrawArrays(__test_vbo->draw_type, 0, 3);
    
    D_swap_window_buffers();
    D_poll_window_events();
  }

end_all:  
  D_end_vbo(__test_vbo);
  D_end_vao(__test_vao);
  glDeleteProgram(shader_program);

  D_end_window(window);
  D_end();

  return 0;
}

bool
_shader()
{
  i32 success;
  char infoLog[512];
  
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader);
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);

    return false;
  }

  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
  glCompileShader(fragment_shader);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);

    return false;
  }
  
  shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);

  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(shader_program, 512, NULL, infoLog);

    return false;
  }
  
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  return true;
}
