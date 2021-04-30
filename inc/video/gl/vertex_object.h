/**
 * \file inc/video/gl/vertex_object.h
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

#ifndef __D_VERTEX_OBJECT_H__
#define __D_VERTEX_OBJECT_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "core/core.h"
#include "video/video.h"

#define D_VO_NONE 0x0  
#define D_VBO_ARRAY  0x1
#define D_VBO_BUFFER 0x2
#define D_VBO_ALL    0x3

struct D_vertex_object
{
  u32 array_object,
      buffer_object,
      buffer_type,
      draw_type,
      draw_mode;
};

struct D_vertex_object *
D_create_vertex_object(u32 __buffer_type,
                       u32 __draw_type,
                       u32 __draw_mode);

void
D_end_vertex_object(struct D_vertex_object *__vertex_object);

void
D_bind_vertex_buffer_object(struct D_vertex_object *__vertex_object);

void
D_bind_vertex_array_object(struct D_vertex_object *__vertex_object);

void
D_unbind_vertex_buffer_object();  

void
D_unbind_vertex_array_object();
  
void
D_vertex_buffer_object_data(struct D_vertex_object *__vertex_object,
                            void                   *__data,
                            u32                     __count);

/*
 * TODO(J0sueTM)
void
D_vertex_array_object_attrib_pointer(struct D_vertex_object *__vertex_object,
);
*/

#ifdef _cplusplus
}
#endif /* __cplusplus */

#endif /* __D_VBO_H__ */
