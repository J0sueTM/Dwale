/**
 * \file inc/video/gl/texture.h
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date May 16, 2021
 *
 * \brief Texture related functionalities
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

#ifndef __D_TEXTURE_H__
#define __D_TEXTURE_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "core/core.h"
#include "video/video.h"
#include "video/gl/stb_image.h"

#define TEXTURE_UNIT(x) GL_TEXTURE0 + x

struct D_texture
{
  unsigned int handle, type, format;
  int width, height, nr_channels, unit;
};

/**
 * \brief Creates a new texture from given file.
 *
 * \param __file_name    Specifies the path (local or full) to the image file.
 * \param __type         Specifies the texture type: GL_TEXTURE_2D or GL_TEXTURE_1D.
 * \param __wrap_s       Specifies the left wrapping method.
 * \param __wrap_t       Specifies the right wrapping method.
 * \param __filter_s     Specifies the left filtering method: GL_NEAREST or GL_LINEAR.
 * \param __filter_t     Specifies the right filtering method: GL_NEAREST OR gl_LINEAR.
 * \param __format       Specifies the image formate: GL_RGB, GL_RGBA, etc.
 * \param __flip         Specifies whether or not the loaded image should be flipped on memory.
 * \param __texture_unit Specifies the shader unit for the created texture.
 *                       NOTE(all): Make sure the gpu supports the amount of textures you're setting
 *                       per shader. The standard is 16 so try to follow that.
 *
 * \return The created texture.
 */
struct D_texture *
D_create_texture(char         *__file_name,
                 unsigned int  __type,
                 unsigned int  __wrap_s,
                 unsigned int  __wrap_t,
                 unsigned int  __filter_s,
                 unsigned int  __filter_t,
                 unsigned int  __format,
                 bool          __flip,
                 int           __texture_unit);

/**
 * \brief Ends given texture. Ends dependencies and frees allocated memory.
 */
void
D_end_texture(struct D_texture *__texture);

/**
 * \brief Binds given texture.
 */
void
D_bind_texture(struct D_texture *__texture);
  
#ifdef __cplusplus
}
#endif /* __cplusplus */
  
#endif /* __D_TEXTURE_H__ */
