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
  u32 handle,
      type,
      format;
  i32 width,
      height,
      nr_channels,
      unit;
};

struct D_texture *
D_create_texture(char *__file_name,
                 u32   __type,
                 u32   __wrap_s,
                 u32   __wrap_t,
                 u32   __filter_s,
                 u32   __filter_t,
                 u32   __format,
                 bool  __flip,
                 i32   __texture_unit);

void
D_end_texture(struct D_texture *__texture);

void
D_bind_texture(struct D_texture *__texture);
  
#ifdef __cplusplus
}
#endif /* __cplusplus */
  
#endif /* __D_TEXTURE_H__ */
