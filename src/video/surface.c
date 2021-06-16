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
D_create_rectangle_surface(struct D_surface *__surface)
{
  if (!__surface)
  {
    D_raise_error(DERR_NOPARAM("__surface", "Surface can't be NULL"));

    return;
  }

  __surface->vct = (float *)malloc(sizeof(float) * 32);
  D_assert(__surface->vct, NULL);
  __surface->vi = (unsigned int *)malloc(sizeof(unsigned int) * 6);
  D_assert(__surface->vi, NULL);
  memset(__surface->vct, 0x00, sizeof(float) * 32);
  memset(__surface->vi, 0x00, sizeof(unsigned int) * 6);

  /*
  {
    __surface->shape.rectangle.right_top[0], __surface->shape.rectangle.right_top[1], 0.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,
    __surface->shape.rectangle.right_bottom[0], __surface->shape.rectangle.right_bottom[1], 0.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 0.0f,
    __surface->shape.rectangle.left_bottom[0], __surface->shape.rectangle.left_bottom[1], 0.0f,
    1.0f, 1.0f, 1.0f,
    0.0f, 0.0f,
    __surface->shape.rectangle.left_top[0], __surface->shape.rectangle.left_top[1], 0.0f,
    1.0f, 1.0f, 1.0f,
    0.0f, 1.0f
  };

  { 0, 1, 3, 1, 2, 3 };
  */

  /* vertices */
  *(__surface->vct + 0) = __surface->shape.rectangle.right_top[0];
  *(__surface->vct + 1) = __surface->shape.rectangle.right_top[1];
  *(__surface->vct + 8) = __surface->shape.rectangle.right_bottom[0];
  *(__surface->vct + 9) = __surface->shape.rectangle.right_bottom[1];
  *(__surface->vct + 16) = __surface->shape.rectangle.left_bottom[0];
  *(__surface->vct + 17) = __surface->shape.rectangle.left_bottom[1];
  *(__surface->vct + 24) = __surface->shape.rectangle.left_top[0];
  *(__surface->vct + 25) = __surface->shape.rectangle.left_top[1];

  /* colours */
  for (int i = 3; i < 30; i += 8)
  {
    *(__surface->vct + i) = 1.0f;
    *(__surface->vct + i + 1) = 1.0f;
    *(__surface->vct + i + 2) = 1.0f;
  }

  /* texture coordinates */
  *(__surface->vct + 6) = 1.0f;
  *(__surface->vct + 7) = 1.0f;
  *(__surface->vct + 14) = 1.0f;
  *(__surface->vct + 31) = 1.0f;

  /* vertices indices */
  *(__surface->vi + 1) = 1;
  *(__surface->vi + 2) = 3;
  *(__surface->vi + 3) = 1;
  *(__surface->vi + 4) = 2;
  *(__surface->vi + 5) = 3;

  __surface->vao = D_create_vao();
  __surface->vbo = D_create_vbo(GL_ARRAY_BUFFER, __surface->draw_type, __surface->draw_mode);
  __surface->ebo = D_create_vbo(GL_ELEMENT_ARRAY_BUFFER, __surface->draw_type, __surface->draw_mode);

  D_bind_vao(__surface->vao);
  D_vbo_data(__surface->vbo, sizeof(float) * 32, __surface->vct);
  D_vbo_data(__surface->ebo, sizeof(unsigned int) * 6, __surface->vi);

  D_vao_attrib_pointer(__surface->vao, 0, 3, GL_FLOAT, sizeof(float) * 8, 0); /* vertices */
  D_vao_attrib_pointer(__surface->vao, 1, 3, GL_FLOAT, sizeof(float) * 8, 3); /* colours */
  D_vao_attrib_pointer(__surface->vao, 2, 2, GL_FLOAT, sizeof(float) * 8, 6); /* texture coordinates */

  __surface->ebo_count = 6;
  __surface->ebo_type = GL_UNSIGNED_INT;
}

struct D_surface *
D_create_surface(enum D_surface_shape  __shape,
                 ...)
{
  struct D_surface *new_surface = (struct D_surface *)malloc(sizeof(struct D_surface));
  D_assert(new_surface, NULL);
  glm_mat4_identity(new_surface->model);

  va_list surface_arg_list;
  va_start(surface_arg_list, __shape);

  new_surface->draw_type = GL_TRIANGLES;
  new_surface->draw_mode = va_arg(surface_arg_list, unsigned int);
  new_surface->rotation = 0.0f;
  glm_vec2_one(new_surface->pivot);
  glm_vec2_zero(new_surface->position);
  glm_vec2_one(new_surface->scale);
  
  switch (__shape)
  {
  case D_SURFACE_RECTANGLE:
    new_surface->shape.rectangle.left_bottom[0]  = (float)va_arg(surface_arg_list, double);
    new_surface->shape.rectangle.left_bottom[1]  = (float)va_arg(surface_arg_list, double);
    new_surface->shape.rectangle.left_top[0]     = (float)va_arg(surface_arg_list, double);
    new_surface->shape.rectangle.left_top[1]     = (float)va_arg(surface_arg_list, double);
    new_surface->shape.rectangle.right_top[0]    = (float)va_arg(surface_arg_list, double);
    new_surface->shape.rectangle.right_top[1]    = (float)va_arg(surface_arg_list, double);
    new_surface->shape.rectangle.right_bottom[0] = (float)va_arg(surface_arg_list, double);
    new_surface->shape.rectangle.right_bottom[1] = (float)va_arg(surface_arg_list, double);

    D_create_rectangle_surface(new_surface);

    break;
  case D_SURFACE_TRIANGLE:
    /* IMPLEMENT ME */

    break;
  case D_SURFACE_CIRCLE:
    /* IMPLEMENT ME */

    break;
  default:
    D_raise_error(DERR_NOPARAM("__shape", "Invalid surface shape"));

    va_end(surface_arg_list);
    D_end_surface(new_surface);
    return NULL;

    break;
  }
  va_end(surface_arg_list);

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
  /* TODO(J0sueTM): Implement pivot */
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
D_set_surface_pivot(struct D_surface *__surface,
                    vec2              __pivot)
{
  if (!__surface)
    return;

  __surface->pivot[0] = __pivot[0];
  __surface->pivot[1] = __pivot[1];
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
