/**
 * \file inc/video/surface.h
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date May 21, 2021
 *
 * \brief Surface is basically a panel, where gl object can be attached to.
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

#include <math.h>
#include "core/core.h"
#include "video/video.h"
#include "video/gl/shader.h"
#include "video/gl/texture.h"
#include "video/gl/gl_object.h"
#include "cglm/vec2.h"

/*
 * I'm  sure you'll hardly reach these numbers.
 * In any case, just change them and make sure the GPU supports the new values.
 */
#define D_MAX_TEXTURES_ON_SURFACE 16

struct D_texture_node
{
  /*
   * NOTE(all): It's not a bad design choice to put these here
   * I could put them inside the texture struct, but I want them to be
   * local options on the surface.
   * If I use the same texture on two different surfaces and I want to
   * disable just the one on the first surface and/or vice versa, I can.
   * Also, I want to be able to give different names for textures dependending
   * on the surface they're attached to.
   */
  char *name;
  bool status;
  i32 id;
  struct D_texture *texture;
  struct D_texture_node *next;
  struct D_texture_node *prev;
};

struct D_surface
{
  f32 *vct; /* vertices, colors and texture coordinates */
  u32 *vi; /* vertices indices (EBO) */
  
  struct D_vao *vao;
  struct D_vbo *vbo;
  struct D_vbo *ebo;

  struct D_shaders *shaders;  

  /*
   * NOTE(all): Since rendering works as a layer of all rendering contexts,
   * textures are stacked(linked) into this implementation of linked list.
   *
   * For performance reasons, it will he faster to begin iterating from the tail,
   * if the node is nearer to it than to the head.
   */
  struct D_texture_node *head_texture_node;
  struct D_texture_node *tail_texture_node;
  u32 ebo_count, ebo_type;
};

struct D_surface *
D_create_surface(u32               __vct_size,
                 f32              *__vct,
                 u32               __vi_size,
                 u32              *__vi,
                 u32               __stride,
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

struct D_texture_node *
D_get_texture_node_with_texture(struct D_surface *__surface,
                                struct D_texture *__texture);

bool
D_is_texture_enabled(struct D_surface *__surface,
                     struct D_texture *__texture);
  
void
D_set_surface_texture_status(struct D_surface *__surface,
                             struct D_texture *__texture,
                             bool              __status);

void
D_bind_textures_from_surface(struct D_surface *__surface);

void
D_prepare_surface_for_rendering(struct D_surface *__surface);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_SURFACE_H__ */
