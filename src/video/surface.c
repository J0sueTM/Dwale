/**
 * \file src/video/surface.c
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

#include "video/surface.h"

struct D_surface *
D_create_surface(unsigned int      __vct_size,
                 float            *__vct,
                 unsigned int      __vi_size,
                 unsigned int     *__vi,
                 unsigned int      __stride,
                 unsigned int      __draw_type,
                 unsigned int      __draw_mode,
                 unsigned int      __ebo_count,
                 unsigned int      __ebo_type,
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
  new_surface->shaders = __shaders;
  new_surface->ebo_count = __ebo_count;
  new_surface->ebo_type = __ebo_type;

  new_surface->vao = D_create_vao();
  new_surface->vbo = D_create_vbo(GL_ARRAY_BUFFER, __draw_type, __draw_mode);
  if (new_surface->vi)
    new_surface->ebo = D_create_vbo(GL_ELEMENT_ARRAY_BUFFER, __draw_type, __draw_mode);

  D_bind_vao(new_surface->vao);
  D_vbo_data(new_surface->vbo, __vct_size, new_surface->vct);
  if (new_surface->vi)
    D_vbo_data(new_surface->ebo, __vi_size, new_surface->vi);

  D_vao_attrib_pointer(new_surface->vao, 0, 3, GL_FLOAT, __stride * sizeof(float), 0); /* vertices */
  D_vao_attrib_pointer(new_surface->vao, 1, 3, GL_FLOAT, __stride * sizeof(float), 3); /* colors */
  D_vao_attrib_pointer(new_surface->vao, 2, 2, GL_FLOAT, __stride * sizeof(float), 6); /* texture coords */

  new_surface->head_texture_node = (struct D_texture_node *)malloc(sizeof(struct D_texture_node));
  D_assert(new_surface->head_texture_node, NULL);
  new_surface->head_texture_node->id = -1;
  new_surface->head_texture_node->texture = NULL;
  new_surface->head_texture_node->name = NULL;
  new_surface->head_texture_node->status = false;
  new_surface->head_texture_node->next = NULL;
  new_surface->head_texture_node->prev = NULL;
  new_surface->tail_texture_node = new_surface->head_texture_node;

  D_raise_log("Created surface");
  return new_surface;
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
    D_end_vbo(__surface->ebo);

  while (__surface->tail_texture_node->id >= 0)
    D_pop_texture_from_surface(__surface);

  D_raise_log("Ended surface");
}

bool
D_surface_has_texture(struct D_surface *__surface,
                      struct D_texture *__texture)
{
  if (!__surface ||
      !__texture)
    return false;
  else if (__surface->tail_texture_node->id == -1)
    return false;
  
  struct D_texture_node *temp_head_texture_node = __surface->head_texture_node;
  struct D_texture_node *temp_tail_texture_node = __surface->tail_texture_node;
  for (int i = 0; i < ceill(__surface->tail_texture_node->id * 0.5f); ++i)
  {
    if (temp_head_texture_node->texture == __texture ||
        temp_tail_texture_node->texture == __texture)
      return true;
    else if (temp_head_texture_node == temp_tail_texture_node)
      return false;

    if (temp_head_texture_node->next)
      temp_head_texture_node = temp_head_texture_node->next;
    if (temp_tail_texture_node->prev)
      temp_tail_texture_node = temp_tail_texture_node->prev;
  }

  return false;
}

void
D_push_texture_to_surface(struct D_surface *__surface,
                          struct D_texture *__texture,
                          char             *__name)
{
  if (!__surface ||
      !__texture)
  {
    D_raise_error(DERR_NOPARAM("__surface || __texture", "Surface and/or texture can't be NULL"));

    return;
  }
  else if (__surface->tail_texture_node->id == D_MAX_TEXTURES_ON_SURFACE)
  {
    D_raise_warning("Surface has already it's maximum of textures");

    return;
  }
  else if (D_surface_has_texture(__surface, __texture))
    return;

  struct D_texture_node *new_texture_node = (struct D_texture_node *)malloc(sizeof(struct D_texture_node));
  D_assert(new_texture_node, NULL);
  new_texture_node->texture = __texture;
  new_texture_node->status = true;
  new_texture_node->name = __name;
  new_texture_node->next = NULL;

  new_texture_node->prev = __surface->tail_texture_node;
  __surface->tail_texture_node->next = new_texture_node;
  __surface->tail_texture_node = new_texture_node;
  new_texture_node->id = new_texture_node->prev->id + 1;

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
  else if (__surface->tail_texture_node->id == -1)
    return;

  struct D_texture_node *temp_next_tail_texture_node = __surface->tail_texture_node->prev;
  free(__surface->tail_texture_node);
  __surface->tail_texture_node = temp_next_tail_texture_node;
  
  D_raise_log("Popped texture from surface");
}

struct D_texture_node *
D_get_texture_node_with_texture(struct D_surface *__surface,
                                struct D_texture *__texture)
{
  if (!__surface ||
      !__texture)
    return NULL;
  else if (__surface->tail_texture_node->id == -1)
    return NULL;
  
  struct D_texture_node *temp_head_texture_node = __surface->head_texture_node;
  struct D_texture_node *temp_tail_texture_node = __surface->tail_texture_node;
  for (int i = 0; i < ceill(__surface->tail_texture_node->id * 0.5f); ++i)
  {
    if (temp_head_texture_node->texture == __texture)
      return temp_head_texture_node;
    else if (temp_tail_texture_node->texture == __texture)
      return temp_tail_texture_node;
    else if (temp_head_texture_node == temp_tail_texture_node)
      return NULL;

    if (temp_head_texture_node->next)
      temp_head_texture_node = temp_head_texture_node->next;
    if (temp_tail_texture_node->prev)
      temp_tail_texture_node = temp_tail_texture_node->prev;
  }

  return false;
}

bool
D_is_texture_enabled(struct D_surface *__surface,
                     struct D_texture *__texture)
{
  if (!__surface ||
      !__texture)
  {
    D_raise_error(DERR_NOPARAM("__surface || __texture", "Surface and/or texture can't be NULL"));

    return false;
  }

  if (D_surface_has_texture(__surface, __texture))
    return D_get_texture_node_with_texture(__surface, __texture)->status;
}

void
D_set_surface_texture_status(struct D_surface *__surface,
                             struct D_texture *__texture,
                             bool              __status)
{
  if (!D_surface_has_texture(__surface, __texture))
    return;

  D_get_texture_node_with_texture(__surface, __texture)->status = __status;
}

void
D_bind_textures_from_surface(struct D_surface *__surface)
{
  if (!__surface)
  {
    D_raise_error(DERR_NOPARAM("__surface", "Surface can't be NULL"));

    return;
  }
  
  struct D_texture_node *temp_head_texture_node = __surface->head_texture_node->next;
  while (temp_head_texture_node)
  {
    if (temp_head_texture_node->status)
      D_bind_texture(temp_head_texture_node->texture);

    temp_head_texture_node = temp_head_texture_node->next;
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

  int i = 0;
  struct D_texture_node *temp_head_texture_node = __surface->head_texture_node->next;
  while (temp_head_texture_node)
  {
    D_set_uniform_int(__surface->shaders, i, temp_head_texture_node->name);

    temp_head_texture_node = temp_head_texture_node->next;
    ++i;
  }
}
