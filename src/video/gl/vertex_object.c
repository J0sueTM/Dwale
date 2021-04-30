/**
 * \file src/video/gl/vertex_object.c
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date April 24, 2021
 *
 * \brief Vertex Buffer Object related functionalities
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

#include "video/gl/vertex_object.h"

struct D_vertex_object *
D_create_vertex_object(u32 __buffer_type,
                       u32 __draw_type,
                       u32 __draw_mode)
{
  struct D_vertex_object *new_vertex_object =
    (struct D_vertex_object *)malloc(sizeof(struct D_vertex_object));
  D_assert(new_vertex_object, NULL);

  glGenVertexArrays(1, &new_vertex_object->array_object);
  glGenBuffers(1, &new_vertex_object->buffer_object);
  new_vertex_object->buffer_type = __buffer_type;
  new_vertex_object->draw_type   = __draw_type;
  new_vertex_object->draw_mode   = __draw_mode;

  D_raise_log("Created vertex object");
  return new_vertex_object;
}

void
D_end_vertex_object(struct D_vertex_object *__vertex_object)
{
  glDeleteVertexArrays(1, &__vertex_object->array_object);
  glDeleteBuffers(1, &__vertex_object->buffer_object);

  D_raise_log("Ended vertex object");
}

void
D_bind_vertex_buffer_object(struct D_vertex_object *__vertex_object)
{ glBindBuffer(__vertex_object->buffer_type, __vertex_object->buffer_object); }

void
D_bind_array_object(struct D_vertex_object *__vertex_object)
{ glBindVertexArray(__vertex_object->array_object); }

void
D_unbind_vertex_buffer_object()
{ glBindBuffer(GL_ARRAY_BUFFER, D_VO_NONE); }

void
D_unbind_vertex_array_object()
{ glBindVertexArray(D_VO_NONE); }

void
D_vertex_buffer_object_data(struct D_vertex_object *__vertex_object,
                            void                   *__data,
                            u32                     __count)
{
  D_bind_vertex_buffer_object(__vertex_object);
  glBufferData(__vertex_object->buffer_type, __count * sizeof(*__data), __data, __vertex_object->draw_mode);
}
