/**
 * \file src/video/gl/shader.c
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date May 02, 2021
 *
 * \brief Vertex Shader related functionalities
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

#include "video/gl/shader.h"

struct D_shader *
D_create_shader(char *__vertex_shader_file,
                char *__fragment_shader_file)
{
  /* I would use access or stat for checking file existence.
   * But, neither of those are POSIX & WIN compliant. So, this is my best bet.
   */
  FILE *test_file;
  test_file = fopen(__vertex_shader_file, "r");
  D_assert(test_file, NULL);

  test_file = fopen(__fragment_shader_file, "r");
  D_assert(test_file, NULL);

  const char *vertex_shader_source;
  const char *fragment_shader_source;

  return D_create_shader_from_string(vertex_shader_source, fragment_shader_source);
}

struct D_shader *
D_create_shader_from_string(const char *__vertex_shader_source,
                            const char *__fragment_shader_source)
{
  struct D_shader *new_shader = (struct D_shader *)malloc(sizeof(struct D_shader *));
  D_assert(new_shader, NULL);

  D_raise_log("Created shader");
  return new_shader;
}
