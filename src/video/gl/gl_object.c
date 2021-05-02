/**
 * \file src/video/gl/gl_object.c
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date May 01, 2021
 *
 * \brief Vertex Buffer and Vertex Array Object related functionalities
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

#include "video/gl/gl_object.h"

struct D_vbo *
D_create_vbo(u32 __buffer_type,
             u32 __draw_type,
             u32 __draw_mode)
{
  struct D_vbo *new_vbo = (struct D_vbo *)malloc(sizeof(struct D_vbo));
  D_assert_fatal(new_vbo, NULL);

  glGenBuffers(1, &new_vbo->handle);
  new_vbo->buffer_type = __buffer_type;
  new_vbo->draw_type   = __draw_type;
  new_vbo->draw_mode   = __draw_mode;

  D_raise_log("Created vertex buffer object");
  return new_vbo;
}

struct D_vao *
D_create_vao()
{
  struct D_vao *new_vao = (struct D_vao *)malloc(sizeof(struct D_vao));
  D_assert_fatal(new_vao, NULL);

  glGenVertexArrays(1, &new_vao->handle);

  D_raise_log("Created vertex array object");
  return new_vao;
}

void
D_end_vbo(struct D_vbo *__vbo)
{
  if (!__vbo)
  {
    D_raise_error(DERR_NOPARAM("__vbo", "VBO can't be NULL"));

    return;
  }

  glDeleteBuffers(1, &__vbo->handle);

  D_raise_log("Ended vertex buffer object");
}

void
D_end_vao(struct D_vao *__vao)
{
  if (!__vao)
  {
    D_raise_error(DERR_NOPARAM("__vao", "VAO can't be NULL"));

    return;
  }

  glDeleteVertexArrays(1, &__vao->handle);

  D_raise_log("Ended vertex array object");
}

void
D_bind_vbo(struct D_vbo *__vbo)
{ glBindBuffer(__vbo->buffer_type, __vbo->handle); }

void
D_bind_vao(struct D_vao *__vao)
{ glBindVertexArray(__vao->handle); }

/* NOTE(all): Does the same as calling D_bind_vbo((struct D_vbo *)0),
 * but makes code more readable
 */
void
D_unbind_vbo()
{ glBindBuffer(GL_ARRAY_BUFFER, D_VO_NONE); }

/* NOTE(all): Does the same as calling D_bind_vao((struct D_vao *)0),
 * but makes code more readable
 */
void
D_unbind_vao()
{ glBindVertexArray(D_VO_NONE); }

void
D_vbo_data(struct D_vbo *__vbo,
           u32           __size,
           void         *__data)
{
  if (!__vbo)
  {
    D_raise_error(DERR_NOPARAM("__vbo", "VBO can't be NULL"));

    return;
  }

  D_bind_vbo(__vbo);
  glBufferData(__vbo->buffer_type,  __size, __data, __vbo->draw_mode);
}

void
D_vao_attrib_pointer(struct D_vao *__vao,
                     struct D_vbo *__vbo,
                     u32						__index,
                     i32						__size,
                     u32						__type,
                     u32						__stride,
                     size_t				__offset)
{
  if (!__vbo)
  {
    D_raise_error(DERR_NOPARAM("__vbo", "VBO can't be NULL"));

    return;
  }
  else if (!__vao)
  {
    D_raise_error(DERR_NOPARAM("__vao", "VAO can't be NULL"));

    return;
  }

  D_bind_vao(__vao);
  D_bind_vbo(__vbo);

  if (__type == GL_UNSIGNED_INT_2_10_10_10_REV)
  { glVertexAttribIPointer(__index, __size, __type, __stride, (void *)__offset); }
  else
  { glVertexAttribPointer(__index, __size, __type, GL_FALSE, __stride, (void *)__offset); }

  glEnableVertexAttribArray(__index);
}
