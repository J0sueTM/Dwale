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

static void
_end_surface_creation(struct D_surface *__surface)
{
  if (!__surface)
    return;

  __surface->ebo_type = GL_UNSIGNED_INT;
  __surface->rotation = 0.0f;

  glm_mat4_identity(__surface->model);
  glm_vec2_zero(__surface->position);
  glm_vec2_one(__surface->scale);
  glm_vec2_zero(__surface->uv_shift);

  __surface->head_texture_node = (struct D_texture_node *)malloc(sizeof(struct D_texture_node));
  D_assert(__surface->head_texture_node, NULL);
  __surface->head_texture_node->id = -1;
  __surface->head_texture_node->texture = NULL;
  __surface->head_texture_node->name = NULL;
  __surface->head_texture_node->status = false;
  __surface->head_texture_node->next = NULL;
  __surface->head_texture_node->prev = NULL;

  __surface->tail_texture_node = __surface->head_texture_node;

  D_raise_log("Created surface");
}

struct D_surface *
D_create_rectangle_surface(unsigned int __draw_mode,
                           vec2         __left_bottom,
                           vec2         __left_top,
                           vec2         __right_top,
                           vec2         __right_bottom,
                           unsigned int __columns,
                           unsigned int __rows)
{
  struct D_surface *new_surface = (struct D_surface *)malloc(sizeof(struct D_surface));
  D_assert(new_surface, NULL);
  new_surface->draw_mode = __draw_mode;
  new_surface->draw_type = GL_TRIANGLES;

  new_surface->vertices_uv = (float *)malloc(sizeof(float) * 20);
  D_assert(new_surface->vertices_uv, NULL);
  new_surface->vertices_indices = (unsigned int *)malloc(sizeof(unsigned int) * 6);
  D_assert(new_surface->vertices_indices, NULL);

  memset(new_surface->vertices_uv, 0x00, sizeof(float) * 20);
  memset(new_surface->vertices_indices, 0x00, sizeof(unsigned int) * 6);

  /*
   * right_top[0], right_top[1], 0.0f, right_top_uv[0], right_top_uv[1],
   * right_bottom[0], right_bottom[1], 0.0f, right_bottom_uv[0], right_bottom_uv[1],
   * left_bottom[0], left_bottom[1], 0.0f, left_bottom_uv[0], left_bottom_uv[1],
   * left_top[0], left_top[1], 0.0f, left_top_uv[0], left_top_uv[1]
   */

  /* vertices */
  *(new_surface->vertices_uv + 0)  = __right_top[0];
  *(new_surface->vertices_uv + 1)  = __right_top[1];
  *(new_surface->vertices_uv + 5)  = __right_bottom[0];
  *(new_surface->vertices_uv + 6)  = __right_bottom[1];
  *(new_surface->vertices_uv + 10) = __left_bottom[0];
  *(new_surface->vertices_uv + 11) = __left_bottom[1];
  *(new_surface->vertices_uv + 15) = __left_top[0];
  *(new_surface->vertices_uv + 16) = __left_top[1];

  /*
  *(new_surface->vertices_uv + 3)  = 1.0f;
  *(new_surface->vertices_uv + 4)  = 1.0f;
  *(new_surface->vertices_uv + 8)  = 1.0f;
  *(new_surface->vertices_uv + 19) = 1.0f;
  */
  /* uv */
  *(new_surface->vertices_uv + 3)  = (float)(1.0f / __columns);
  *(new_surface->vertices_uv + 4)  = (float)(1.0f / __rows);
  *(new_surface->vertices_uv + 8)  = (float)(1.0f / __columns);
  *(new_surface->vertices_uv + 19) = (float)(1.0f / __rows);

  /* vertices indices */
  *(new_surface->vertices_indices + 1) = 1;
  *(new_surface->vertices_indices + 2) = 3;
  *(new_surface->vertices_indices + 3) = 1;
  *(new_surface->vertices_indices + 4) = 2;
  *(new_surface->vertices_indices + 5) = 3;

  new_surface->vao = D_create_vao();
  new_surface->vbo = D_create_vbo(GL_ARRAY_BUFFER, new_surface->draw_type, new_surface->draw_mode);
  new_surface->ebo = D_create_vbo(GL_ELEMENT_ARRAY_BUFFER, new_surface->draw_type, new_surface->draw_mode);

  D_bind_vao(new_surface->vao);
  D_vbo_data(new_surface->vbo, sizeof(float) * 20, new_surface->vertices_uv);
  D_vbo_data(new_surface->ebo, sizeof(unsigned int) * 6, new_surface->vertices_indices);
  D_vao_attrib_pointer(new_surface->vao, 0, 3, GL_FLOAT, sizeof(float) * 5, 0);
  D_vao_attrib_pointer(new_surface->vao, 1, 2, GL_FLOAT, sizeof(float) * 5, 3);

  new_surface->ebo_count = 6;
  _end_surface_creation(new_surface);

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

  if (__surface->vao)
    D_end_vao(__surface->vao);
  if (__surface->ebo)
    D_end_vbo(__surface->vbo);
  if (__surface->ebo)
    D_end_vbo(__surface->ebo);

  while (__surface->tail_texture_node->id >= 0)
    D_pop_texture_from_surface(__surface);
  if (__surface->head_texture_node)
    free(__surface->head_texture_node);

  D_raise_log("Ended surface");
}

void
D_reset_surface(struct D_surface *__surface)
{
  if (!__surface)
  {
    D_raise_error(DERR_NOPARAM("__surface", "Surface can't be NULL"));

    return;
  }

  glm_mat4_identity(__surface->model);
  glm_translate(__surface->model, __surface->position);
  glm_rotate(__surface->model, -(__surface->rotation), (vec3){ 0.0f, 0.0f, 1.0f });
  glm_scale(__surface->model, __surface->scale);
}

void
D_set_surface_shaders(struct D_surface *__surface,
                      struct D_shaders *__shaders)
{
  if (!__shaders)
  {
    D_raise_error(DERR_NOPARAM("__surface", "Surface can't be NULL"));

    return;
  }
  else if (!__shaders)
  {
    D_raise_error(DERR_NOPARAM("__shaders", "Shaders can't be NULL"));

    return;
  }

  __surface->shaders = __shaders;
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
  new_texture_node->id = __surface->tail_texture_node->id + 1;
  new_texture_node->texture = __texture;
  new_texture_node->status = true;
  new_texture_node->name = __name;
  new_texture_node->next = NULL;
  new_texture_node->prev = __surface->tail_texture_node;
  __surface->tail_texture_node->next = new_texture_node;
  __surface->tail_texture_node = new_texture_node;

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

  D_reset_surface(__surface);
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
  for (struct D_texture_node *temp_head_texture_node = __surface->head_texture_node->next;
       temp_head_texture_node;
       temp_head_texture_node = temp_head_texture_node = temp_head_texture_node->next)
  {
    D_set_uniform_int(__surface->shaders, i, temp_head_texture_node->name);

    ++i;
  }
}

void
D_set_surface_uv_shift(struct D_surface *__surface,
                       unsigned int      __column,
                       unsigned int      __row,
                       vec2              __padding)
{
  if (!__surface)
  {
    D_raise_error(DERR_NOPARAM("__surface", "Surface can't be NULL"));

    return;
  }

  /* The removed padding is calculated by removing the 0 to 1 percentage from the uv unity size */
  __surface->uv_shift[0] = *(__surface->vertices_uv + 3) * (__column + *(__surface->vertices_uv + 3) * __padding[0]);
  __surface->uv_shift[1] = *(__surface->vertices_uv + 4) * (__row + *(__surface->vertices_uv + 4) * __padding[1]);
}

void
D_set_surface_position(struct D_surface *__surface,
                       vec2              __position)
{
  if (!__surface)
    return;

  __surface->position[0] = __position[0];
  __surface->position[1] = __position[1];
}

void
D_translate_surface(struct D_surface *__surface,
                    vec2              __translation)
{
  if (!__surface)
    return;
  
  __surface->position[0] += __translation[0];
  __surface->position[1] += __translation[1];
}

void
D_set_surface_rotation(struct D_surface *__surface,
                       float             __rotation)
{
  if (!__surface)
    return;

  __surface->rotation = __rotation;
}

void
D_rotate_surface(struct D_surface *__surface,
                 float             __rotation)
{
  if (!__surface)
    return;

  __surface->rotation += (__rotation);
}

void
D_set_surface_scale(struct D_surface *__surface,
                    vec2              __scale)
{
  if (!__surface)
    return;

  __surface->scale[0] = __scale[0];
  __surface->scale[1] = __scale[1];
}

void
D_scale_surface(struct D_surface *__surface,
                vec2              __scale)
{
  if (!__surface)
    return;

  __surface->scale[0] *= __scale[0];
  __surface->scale[1] *= __scale[1];
}
