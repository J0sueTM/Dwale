/**
 * \file inc/video/gl/gl_object.h
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

#ifndef __D_GL_OBJECT_H__
#define __D_GL_OBJECT_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "core/core.h"
#include "video/video.h"

#define D_VO_NONE    0x0
#define D_VBO_ARRAY  0x1
#define D_VBO_BUFFER 0x2
#define D_VBO_ALL    0x3

struct D_vbo
{
  u32 handle,
      buffer_type,
      draw_type,
      draw_mode;
};

struct D_vao
{ u32 handle; };

/**
 * \brief Creates a new vertex array object.
 *
 * \param __buffer_type Specifies the OpenGL vertex buffer type,
 *                       used on binding proccess.
 * \param __draw_type   Specifies the OpenGL vertex buffer draw type.
 * \param __draw_mode   Specifies the OPenGL vertex buffer draw mode.
 */
struct D_vbo *
D_create_vbo(u32 __buffer_type,
             u32 __draw_type,
             u32 __draw_mode);

/**
 * \brief Creates a new vertex array object.
 */
struct D_vao *
D_create_vao();

void
D_end_vbo(struct D_vbo *__vbo);

void
D_end_vao(struct D_vao *__vao);

void
D_bind_vbo(struct D_vbo *__vbo);

void
D_bind_vao(struct D_vao *__vao);

void
D_unbind_vbo();

void
D_unbind_vao();

void
D_vbo_data(struct D_vbo *__vbo,
           u32           __size,
           void         *__data);

void
D_vao_attrib_pointer(struct D_vao *__vao,
                     struct D_vbo *__vbo,
                     u32           __index,
                     i32           __size,
                     u32           __type,
                     u32           __stride,
                     size_t        __offset);


#ifdef _cplusplus
}
#endif /* __cplusplus */

#endif /* __D_GL_OBJECT_H__ */
