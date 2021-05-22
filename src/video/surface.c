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
D_create_surface(f32 *__vct,
                 u32 *__vi,
                 u32  __draw_type,
                 u32  __draw_mode)
{
  if (!__vct)
  {
    D_raise_error(DERR_NOPARAM("__vct", "Vertex can't be NULL"));

    return NULL;
  }

  struct D_surface *new_surface = (struct D_surface *)malloc(sizeof(struct D_surface));
  D_assert(new_surface, NULL);
  new_surface->texture_count = new_surface->shaders_count = 0;
  new_surface->vct = __vct;
  new_surface->vi = __vi;

  new_surface->vao = D_create_vao();
  new_surface->vbo = D_create_vbo(GL_ARRAY_BUFFER, __draw_type, __draw_mode);
  new_surface->ebo = D_create_vbo(GL_ELEMENT_ARRAY_BUFFER, __draw_type, __draw_mode);

  D_bind_vao(new_surface->vao);
  D_vbo_data(new_surface->vbo, sizeof(new_surface->vct), new_surface->vct);
  if (new_surface->vi)
  { D_vbo_data(new_surface->ebo, sizeof(new_surface->vi), new_surface->vi); }

  D_vao_attrib_pointer(new_surface->vao, 0, 3, GL_FLOAT, 6 * sizeof(float), 0); /* vertices */
  D_vao_attrib_pointer(new_surface->vao, 1, 1, GL_FLOAT, 6 * sizeof(float), 3); /* colours */
  D_vao_attrib_pointer(new_surface->vao, 2, 2, GL_FLOAT, 6 * sizeof(float), 4); /* texture coords */

  new_surface->textures = (struct D_texture **)malloc(D_MAX_TEXTURES_ON_SURFACE * sizeof(struct D_texture *));
  D_assert(new_surface->textures, NULL);
  new_surface->shaders = (struct D_shaders **)malloc(D_MAX_SHADERS_ON_SURFACE * sizeof(struct D_texture *));
  D_assert(new_surface->shaders, NULL);
  
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
  if (__surface->shaders)
  {
    for (i32 i = 0; i < __surface->shaders_count; ++i)
    { D_end_shaders(__surface->shaders[i]); }
  }

  D_raise_log("Ended surface");
}

bool
D_surface_has_texture(struct D_surface *__surface,
                      struct D_texture *__texture)
{
  if (!__surface ||
      !__texture)
  { return false; }
  else if (__surface->texture_count == 0)
  { return false; }
  
  for (i32 i = 0; i < __surface->texture_count; ++i)
  {
    if (__surface->textures[0] == __texture)
    { return true; }
  }

  return false;
}

void
D_push_texture_to_surface(struct D_surface *__surface,
                          struct D_texture *__texture)
{
  if (!__surface ||
      !__texture)
  {
    D_raise_error(DERR_NOPARAM("__surface || __texture", "Surface and texture can't be NULL"));

    return;
  }
  else if (__surface->texture_count + 1 >= D_MAX_SHADERS_ON_SURFACE)
  { return; }

  __surface->textures[__surface->texture_count] = __texture;
  ++__surface->texture_count;
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

  __surface->textures[__surface->texture_count] = NULL;
  --__surface->texture_count;
}

void
D_push_shaders_to_surface(struct D_surface *__surface,
                          struct D_shaders *__shaders)
{
  if (!__surface ||
      !__shaders)
  {
    D_raise_error(DERR_NOPARAM("__surface || __shaders", "Surface and shaders can't be NULL"));

    return;
  }
  else if (__surface->shaders_count + 1 >= 0)
  { return; }

  __surface->shaders[__surface->shaders_count] = __shaders;
  ++__surface->shaders_count;
}

void
D_pop_shaders_from_surface(struct D_surface *__surface)
{
  if (!__surface)
  {
    D_raise_error(DERR_NOPARAM("__surface", "Surface can't be NULL"));

    return;
  }
  else if (__surface->shaders_count <= 0)
  { return; }

  __surface->shaders[__surface->shaders_count] = NULL;
  --__surface->shaders_count;  
}
