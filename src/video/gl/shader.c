/**
 * \file src/video/gl/shader.c
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date May 02, 2021
 *
 * \brief GL shaders related functionalities
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

/**
 * \brief Copies file content to C string.
 *
 * \param __source_file Specifies the file whose content will be copied.
 *
 * \return The file's content.
 */
static const char *
_read_from_file_to_string(FILE *__source_file)
{
  if (!__source_file)
  {
    D_raise_error(DERR_NOPARAM("__source_file", "Shader source file can't be NULL and/or it could not be opened"));

    return NULL;
  }

  long source_file_size;
  char *source;
  if (__source_file)
  {
    fseek(__source_file, 0, SEEK_END);
    source_file_size = ftell(__source_file);
    fseek(__source_file, 0, SEEK_SET);

    source = (char *)malloc(source_file_size + 1);
    if (!source)
    {
      D_raise_error("Could not allocate memory for shader source");
      fclose(__source_file);

      return NULL;
    }

    fread((void *)source, 1, source_file_size, __source_file);
    fclose(__source_file);
  }

  /* Replaces the last digit by a NULL termination if it's not already. */
  source[source_file_size] = '\0';

  return (const char *)source;
}

unsigned int
D_create_shader(unsigned int  __type,
                const char   *__shader_source)
{
  unsigned int new_shader;
  int status;
  char log[512];

  new_shader = glCreateShader(__type);
  glShaderSource(new_shader, 1, &__shader_source, NULL);
  glCompileShader(new_shader);

  /* error handling */
  glGetShaderiv(new_shader, GL_COMPILE_STATUS, &status);
  if (!status)
  {
    glGetShaderInfoLog(new_shader, 512, NULL, log);
    if (log)
      D_raise_error(log);
    else
      D_raise_error("Couldn't compile shader");

    return 0;
  }

  D_raise_log("Created shader");
  return new_shader;
}

struct D_shaders *
D_create_shaders(const char *__vertex_shader_source,
                 const char *__fragment_shader_source)
{
  if (!__vertex_shader_source)
  {
    D_raise_error(DERR_NOPARAM("__vertex_shader_source", "Vertex shader's source can't be NULL"));

    return NULL;
  }
  else if (!__fragment_shader_source)
  {
    D_raise_error(DERR_NOPARAM("__fragment_shader_source", "Fragment shader's source can't be NULL"));

    return NULL;
  }

  struct D_shaders *new_shaders = (struct D_shaders *)malloc(sizeof(struct D_shaders));
  D_assert(new_shaders, NULL);

  new_shaders->vertex_shader = D_create_shader(GL_VERTEX_SHADER, __vertex_shader_source);
  if (!new_shaders->vertex_shader)
    return NULL;
  new_shaders->fragment_shader = D_create_shader(GL_FRAGMENT_SHADER, __fragment_shader_source);
  if (!new_shaders->fragment_shader)
    return NULL;

  new_shaders->program = glCreateProgram();
  glAttachShader(new_shaders->program, new_shaders->vertex_shader);
  glAttachShader(new_shaders->program, new_shaders->fragment_shader);
  glLinkProgram(new_shaders->program);

  /* error handling */
  int status;
  char *log;
  glGetProgramiv(new_shaders->program, GL_LINK_STATUS, &status);
  if (!status)
  {
    glGetProgramInfoLog(new_shaders->program, 512, NULL, log);
    if (log)
      D_raise_error(log);
    else
      D_raise_error("couldn't link shaders to program");

    return NULL;
  }
  
  return new_shaders;
}

void
D_end_shaders(struct D_shaders *__shaders)
{
  if (!__shaders)
  {
    D_raise_error(DERR_NOPARAM("__shaders", "Shaders can't be NULL"));

    return;
  }
  
  glDeleteShader(__shaders->vertex_shader);
  glDeleteShader(__shaders->fragment_shader);
  glDeleteProgram(__shaders->program);

  D_raise_log("Ended shader");
}

struct D_shaders *
D_create_shaders_from_file(char *__vertex_shader_source_file_name,
                           char *__fragment_shader_source_file_name)
{
  if (!__vertex_shader_source_file_name)
  {
    D_raise_error(DERR_NOPARAM("__vertex_shader_source_file_name", "Shader source file name can't be NULL"));

    return NULL;
  }
  else if (!__fragment_shader_source_file_name)
  {
    D_raise_error(DERR_NOPARAM("__fragment_shader_source_file_name", "Fragment source file name can't be NULL"));

    return NULL;
  }

  FILE *vertex_shader_source_file = fopen(__vertex_shader_source_file_name, "rb");
  const char *vertex_shader_source = _read_from_file_to_string(vertex_shader_source_file);
  D_assert(vertex_shader_source, NULL);

  FILE *fragment_shader_source_file = fopen(__fragment_shader_source_file_name, "rb");
  const char *fragment_shader_source = _read_from_file_to_string(fragment_shader_source_file);
  D_assert(fragment_shader_source, NULL);

  return D_create_shaders(vertex_shader_source, fragment_shader_source);
}

void
D_apply_shaders(struct D_shaders *__shaders)
{
  if (!__shaders)
  {
    D_raise_error(DERR_NOPARAM("__shaders", "Shaders can't be NULL"));

    return;
  }

  glUseProgram(__shaders->program);
}

void
D_set_uniform_int(struct D_shaders *__shaders,
                  int               __value,
                  char             *__name)
{
  glUniform1i(glGetUniformLocation(__shaders->program, __name), __value);
}

void
D_set_uniform_float(struct D_shaders *__shaders,
                    float             __value,
                    char             *__name)
{
  glUniform1f(glGetUniformLocation(__shaders->program, __name), __value);
}

void
D_set_uniform_bool(struct D_shaders *__shaders,
                   bool              __value,
                   char             *__name)
{
  glUniform1i(glGetUniformLocation(__shaders->program, __name), __value);
}

void
D_set_uniform_vec4(struct D_shaders *__shaders,
                   vec4              __value,
                   char             *__name)
{
  glUniform4f(glGetUniformLocation(__shaders->program, __name), __value[0], __value[1], __value[2], __value[3]);
}

void
D_set_uniform_vec3(struct D_shaders *__shaders,
                   vec3              __value,
                   char             *__name)
{
  glUniform3f(glGetUniformLocation(__shaders->program, __name), __value[0], __value[1], __value[2]);
}

void
D_set_uniform_vec2(struct D_shaders *__shaders,
                   vec2              __value,
                   char             *__name)
{
  glUniform2f(glGetUniformLocation(__shaders->program, __name), __value[0], __value[1]);
}

void
D_set_uniform_mat4(struct D_shaders *__shaders,
                   mat4              __value,
                   char             *__name)
{
  glUniformMatrix4fv(glGetUniformLocation(__shaders->program, __name), 1, GL_FALSE, (float *)__value);
}

void
D_set_uniform_mat3(struct D_shaders *__shaders,
                   mat3              __value,
                   char             *__name)
{
  glUniformMatrix3fv(glGetUniformLocation(__shaders->program, __name), 1, GL_FALSE, (float *)__value);
}

void
D_set_uniform_mat2(struct D_shaders *__shaders,
                   mat2              __value,
                   char             *__name)
{
  glUniformMatrix2fv(glGetUniformLocation(__shaders->program, __name), 1, GL_FALSE, (float *)__value);
}
