/**
 * \file inc/video/surface.h
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date May 21, 2021
 *
 * \brief Surface related functionalities
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

#ifndef __D_SURFACE_H__
#define __D_SURFACE_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "core/core.h"
#include "video/video.h"
#include "video/gl/shader.h"
#include "video/gl/texture.h"
#include "video/gl/gl_object.h"
#include "cglm/vec2.h"

/*
 * I'm  sure you'll never reach these numbers.
 * In any case, just change them and make sure the GPU supports the new values.
 */
#define D_MAX_TEXTURES_ON_SURFACE GL_MAX_TEXTURE_IMAGE_UNITS

struct D_surface
{
  f32 *vct;
  u32 *vi;
  
  struct D_vao *vao;
  struct D_vbo *vbo;
  struct D_vbo *ebo;

  struct D_shaders *shaders;  
  struct D_texture *textures[D_MAX_TEXTURES_ON_SURFACE];
  /*
   * NOTE(all): It's not a bad design choice to put these here
   * I could put them inside the texture struct, but I want them to be
   * local options on the surface.
   * If I use the same texture on two different surfaces and I want to
   * disable just the one on the first surface and/or vice versa, I can.
   * Also, I want to be able to give different names for textures dependending
   * on the surface they're attached to.
   */
  char *textures_names[D_MAX_TEXTURES_ON_SURFACE];
  bool  textures_status[D_MAX_TEXTURES_ON_SURFACE];

  u32 texture_count, ebo_count, ebo_type;
};

struct D_surface *
D_create_surface(f32              *__vct,
                 u32              *__vi,
                 u32               __draw_type,
                 u32               __draw_mode,
                 u32               __ebo_count,
                 u32               __ebo_type,
                 struct D_shaders *__shaders);

void
D_end_surface(struct D_surface *__surface);

bool
D_surface_has_texture(struct D_surface *__surface,
                      struct D_texture *__texture);

bool
D_surface_has_texture_on_position(struct D_surface *__surface,
                                  u32               __position);

void
D_push_texture_to_surface(struct D_surface *__surface,
                          struct D_texture *__texture,
                          char             *__name);

void
D_pop_texture_from_surface(struct D_surface *__surface);

void
D_push_shaders_to_surface(struct D_surface *__surface,
                          struct D_shaders *__shaders);

void
D_pop_shaders_from_surface(struct D_surface *__surface);

bool
D_is_texture_enabled(struct D_surface *__surface,
                     u32               __position);
  
void
D_set_surface_texture_status(struct D_surface *__surface,
                             u32               __position, 
                             bool              __status);

void
D_bind_textures_from_surface(struct D_surface *__surface);

void
D_prepare_surface_for_rendering(struct D_surface *__surface);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_SURFACE_H__ */
