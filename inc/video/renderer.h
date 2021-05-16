/**
 * \file inc/video/renderer.h
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date May 14, 2021
 *
 * \brief Renderer related functionalities
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

#ifndef __D_RENDERER_H__
#define __D_RENDERER_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "core/core.h"
#include "video/video.h"
#include "video/gl/gl_object.h"
#include "video/gl/shader.h"

void
D_draw_arrays(struct D_vao     *__vao,
              struct D_vbo     *__vbo,
              struct D_shaders *__shaders);

void
D_draw_elements(struct D_vao     *__vao,
                struct D_vbo     *__ebo,
                u32               __count,
                u32               __type,
                struct D_shaders *__shaders);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_RENDERER_H__ */
