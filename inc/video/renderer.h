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
#include "video/gl/texture.h"
#include "video/gl/shader.h"
#include "video/surface.h"
#include "video/camera.h"

/**
 * \brief Creates a draw call for the given vertex buffer object.
 *
 * \param __vao     Specifies the vertex array object to be binded with the vertex
 *                  buffer object.
 * \param __vbo     Specifies the vertex buffer object from which attributes will
 *                  be used on the draw call.
 * \param __shaders Specifies the shaders to be applied.
 */
void
D_draw_arrays(struct D_vao     *__vao,
              struct D_vbo     *__vbo,
              struct D_shaders *__shaders);

/**
 * \brief Creates a draw call for the given vertex element array buffer object.
 *
 * \param __vbo     Specifies the vertex array object to be binded with the 
 *                  element array buffer object.
 * \param __ebo     Specifies the vertex element array buffer object from which
 *                  attributes will be used on the draw call.
 * \param __count   Specifies the amount of elements in the element array buffer object.
 * \param __type    Specifies the type of the elemens in the elementa rray buffer object.
 * \param __shaders Specifies the shaders to be applied.
 */
void
D_draw_elements(struct D_vao     *__vao,
                struct D_vbo     *__ebo,
                unsigned int      __count,
                unsigned int      __type,
                struct D_shaders *__shaders);

/**
 * \brief Creates draw calls for the vao attached to the surface.
 *
 * \param __surface Specifies the surface to be drawn.
 * \param __camera  Specifies the camera to be used when rendering the surface.
 *                  NOTE(all): Optional, if it's a static element (Shouldn't be affected by world matrices),
 *                             you don't need to give a camera.
 */
void
D_draw_surface(struct D_surface *__surface,
               struct D_camera  *__camera);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_RENDERER_H__ */
