/**
 * \file src/video/surface.c
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date May 21, 2021
 *
 * \brief Surface is basically a panel, where gl object can be attached together.
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

#include "video/surface.h"

struct D_surface *
D_create_surface(f32              *__vct,
                 u32              *__vi,
                 u32               __draw_type,
                 u32               __draw_mode,
                 u32               __ebo_count,
                 u32               __ebo_type,
                 struct D_shaders *__shaders)
{
  if (!__vct)
  {
    D_raise_error(DERR_NOPARAM("__vct", "Vertex can't be NULL"));

    return NULL;
  }
  else if (!__shaders)
  {
    D_raise_error(DERR_NOPARAM("__shaders", "Shaders can't be NULL"));

    return NULL;
  }

  struct D_surface *new_surface = (struct D_surface *)malloc(sizeof(struct D_surface));
  D_assert(new_surface, NULL);
  new_surface->vct = __vct;
  new_surface->vi = __vi;
  new_surface->ebo_count = __ebo_count;
  new_surface->ebo_type = __ebo_type;
  new_surface->shaders = __shaders;

  new_surface->vao = D_create_vao();
  new_surface->vbo = D_create_vbo(GL_ARRAY_BUFFER, __draw_type, __draw_mode);
  new_surface->ebo = D_create_vbo(GL_ELEMENT_ARRAY_BUFFER, __draw_type, __draw_mode);

  D_bind_vao(new_surface->vao);
  D_vbo_data(new_surface->vbo, sizeof(new_surface->vct), new_surface->vct);
  if (new_surface->vi)
  { D_vbo_data(new_surface->ebo, sizeof(new_surface->vi), new_surface->vi); }

  D_vao_attrib_pointer(new_surface->vao, 0, 3, GL_FLOAT, 8 * sizeof(float), 0); /* vertices */
  D_vao_attrib_pointer(new_surface->vao, 1, 3, GL_FLOAT, 8 * sizeof(float), 3); /* colors */
  D_vao_attrib_pointer(new_surface->vao, 2, 2, GL_FLOAT, 8 * sizeof(float), 6); /* texture coords */

  for (i32 i = 0; i < D_MAX_TEXTURES_ON_SURFACE; ++i)
  { new_surface->textures_status[i] = D_ENABLED; }

  D_raise_log("Created surface");
}

void
D_end_surface(struct D_surface *__surface)
{
  if (!__surface)
  {
    D_raise_error(DERR_NOPARAM("__surface", "Surface can't be NULL"));

    return;
  }

  D_end_vao(__surface->vao);
  D_end_vbo(__surface->vbo);

  if (__surface->ebo)
  { D_end_vbo(__surface->ebo); }
  if (__surface->textures)
  {
    for (i32 i = 0; i < __surface->texture_count; ++i)
    { D_end_texture(__surface->textures[i]); }
  }
  D_end_shaders(__surface->shaders);

  D_raise_log("Ended surface");
}

bool
D_surface_has_texture(struct D_surface *__surface,
                      struct D_texture *__texture)
{
  if (!__surface ||
      !__texture)
  { return false; }
  else if (__surface->texture_count <= 0)
  { return false; }
  
  for (i32 i = 0; i < __surface->texture_count; ++i)
  {
    if (__surface->textures[0] == __texture)
    { return true; }
  }

  return false;
}

bool
D_surface_has_texture_on_position(struct D_surface *__surface,
                                  u32               __position)
{
  if (!__surface)
  {
    D_raise_error(DERR_NOPARAM("__surface", "Surface can't be NULL"));

    return false;
  }
  else if (__position >= __surface->texture_count)
  {
    D_raise_warning("__position out of bound");

    return false;
  }
  
  return D_surface_has_texture(__surface, __surface->textures[__position]);
}

void
D_push_texture_to_surface(struct D_surface *__surface,
                          struct D_texture *__texture,
                          char             *__name)
{
  if (!__surface ||
      !__texture)
  {
    D_raise_error(DERR_NOPARAM("__surface || __texture", "Surface and texture can't be NULL"));

    return;
  }
  else if (__surface->texture_count >= D_MAX_TEXTURES_ON_SURFACE)
  { return; }
  else if (D_surface_has_texture(__surface, __texture))
  { return; }

  __surface->textures[__surface->texture_count] = __texture;
  ++__surface->texture_count;

  if (!__surface->textures_names[__surface->texture_count])
  { __surface->textures_names[__surface->texture_count] = (char *)malloc(1024 * sizeof(char)); }

  D_raise_log("Pushed texture to surface");
}

void
D_pop_texture_from_surface(struct D_surface *__surface)
{
  if (!__surface)
  {
    D_raise_error(DERR_NOPARAM("__surface", "Surface can't be NULL"));

    return;
  }
  else if (__surface->texture_count <= 0)
  { return; }

  __surface->textures[__surface->texture_count - 1] = NULL;
  __surface->textures_names[__surface->texture_count - 1] = NULL;
  D_set_surface_texture_status(__surface, __surface->texture_count - 1, D_DISABLED);
  
  --__surface->texture_count;
  D_raise_log("Popped texture from surface");
}

bool
D_is_texture_enabled(struct D_surface *__surface,
                     u32               __position)
{
  if (!__surface)
  {
    D_raise_error(DERR_NOPARAM("__surface", "Surface can't be NULL"));

    return false;
  }

  return *(__surface->textures_status + __position);
}

void
D_set_surface_texture_status(struct D_surface *__surface,
                             u32               __position,
                             bool              __status)
{
  if (!D_surface_has_texture_on_position(__surface, __position))
  { return; }
  else if (__position >= __surface->texture_count)
  {
    D_raise_warning("__position out of bound");

    return;
  }

  __surface->textures_status[__position] = __status;
}

void
D_bind_textures_from_surface(struct D_surface *__surface)
{
  if (!__surface)
  {
    D_raise_error(DERR_NOPARAM("__surface", "Surface can't be NULL"));

    return;
  }
  
  for (i32 i = 0; i <= __surface->texture_count; ++i)
  {
    if (D_is_texture_enabled(__surface, i))
    { D_bind_texture(__surface->textures[i]); }
  }
}

void
D_prepare_surface_for_rendering(struct D_surface *__surface)
{
  if (!__surface)
  {
    D_raise_error(DERR_NOPARAM("__surface", "Surface can't be NULL"));

    return;
  }

  D_apply_shaders(__surface->shaders);
  for (i32 i = 0; i < __surface->texture_count; ++i)
  {
    if (D_is_texture_enabled(__surface, i))
    {
      D_bind_texture(__surface->textures[i]);
      D_set_uniform_i32(__surface->shaders, __surface->textures[i]->unit, __surface->textures_names[i]);
    }
  }
}
