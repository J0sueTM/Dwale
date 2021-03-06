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
#include "cglm/vec3.h"
#include "cglm/mat4.h"
#include "cglm/affine.h"

/*
 * NOTE(all): It's not a bad design choice to put these here
 * I could put them inside the texture struct, but I want them to be
 * local options on the surface.
 * If I use the same texture on two different surfaces and I want to
 * disable just the one on the first surface and/or vice versa, I can.
 * Also, I want to be able to give different names for textures dependending
 * on the surface they're attached to.
 *
 * NOTE(all): We can have multiple textures into a single surface.
 * However, all of them will be rendered using the same shader.
 * Be aware of that if you're using a tilemap. in this case, just
 * use another surface.
 */
struct D_texture_node
{
  char *name;
  bool status;
  int id;

  struct D_texture *texture;
  struct D_texture_node *next;
  struct D_texture_node *prev;
};

struct D_surface
{
  /* transformation */
  mat4 model;
  vec3 position, scale;
  float rotation;

  vec2 uv_shift;

  float *vertices_uv;
  unsigned int *vertices_indices, draw_type, draw_mode, ebo_count, ebo_type;

  struct D_vao *vao;
  struct D_vbo *vbo;
  struct D_vbo *ebo;
  struct D_shaders *shaders;

  /*
   * NOTE(all): Since rendering works as a layer of all rendering contexts,
   * textures are stacked (linked) into this implementation of linked list.
   *
   * For performance reasons, it will be faster to begin iterating from the tail
   * if the node is closer to it than to the head.
   */
  struct D_texture_node *head_texture_node;
  struct D_texture_node *tail_texture_node;
};

/**
 * \brief Creates a new rectangle shaped surface.
 *
 * \return Created rectangle surface
 */
struct D_surface *
D_create_rectangle_surface(unsigned int __draw_mode,
                           vec2         __left_bottom,
                           vec2         __left_top,
                           vec2         __right_top,
                           vec2         __right_bottom,
                           unsigned int __columns,
                           unsigned int __rows);

/**
 * \brief Ends the surface. Frees memory and dependencies.
 */
void
D_end_surface(struct D_surface *__surface);

/**
 * \brief Resets surface's model matrix.
 *
 * \param __surface Specifies the surface to be reseted.
 */
void
D_reset_surface(struct D_surface *__surface);

/**
 * \brief Sets the shader to be called when rendering given surface.
 *
 * \param __surface Specifies the surface in which __shaders will be attached.
 * \param __shaders Specifies the shader to attech to __surface.
 */
void
D_set_surface_shaders(struct D_surface *__surface,
                      struct D_shaders *__shaders);

/**
 * \brief Checks whether the given __surface has __texture attached or not.
 *
 * \param __surface Specifies the surface where __texture will be searched.
 * \param __texture Specifies the texture to be searched.
 *
 * \return Whether __texture is attached or not.
 */
bool
D_surface_has_texture(struct D_surface *__surface,
                      struct D_texture *__texture);

/**
 * \brief Pushes __texture to __surface rendering stack.
 *
 * \param __surface Specifies the surface where __texture will be pushed into.
 * \param __texture Specifies the texture to be pushed into __surface.
 * \param __name    Specifies the uniform name for __texture thath should be recognisable
 *                  by the shader attached to __surface.
 */
void
D_push_texture_to_surface(struct D_surface *__surface,
                          struct D_texture *__texture,
                          char             *__name);

/**
 * \brief Pops the last pushed texture from __surface.
 *
 * \param __surface Specifies the surface from which the last pushed texture will be removed.
 */
void
D_pop_texture_from_surface(struct D_surface *__surface);

/**
 * \brief Searches for the texture node which has __texture.
 *
 * \param __surface Specifies the __surface in which __texture will be searched for.
 * \param __texture Specifies the texture that should be in the texture node that will be returned.
 *
 * \return The found texture node. NULL otherwise.
 */
struct D_texture_node *
D_get_texture_node_with_texture(struct D_surface *__surface,
                                struct D_texture *__texture);

/**
 * \brief Checks if given texture is enabled for rendering.
 *
 * \param __surface Specifies the surface in which __texture will be searched for.
 * \param __texture Specifies the texture to search for.
 *
 * \return The texture's status. Whether enabled or not.
 */
bool
D_is_texture_enabled(struct D_surface *__surface,
                     struct D_texture *__texture);

/**
 * \brief Sets __texture's status.
 *
 * \param __surface Specifies the surface in which __texture should be.
 * \param __texture Specifies the texture whose status will be setted.
 * \param __status  Specifies the new texture's status. Whether enabled or disabled (true | false).
 */
void
D_set_surface_texture_status(struct D_surface *__surface,
                             struct D_texture *__texture,
                             bool              __status);

/**
 * \brief Dinds all textures in __surface.
 *
 * \param __surface Specifies the surface whose texture will be enabled.
 *                  NOTE(all): textures with false status will not be bound.
 */
void
D_bind_textures_from_surface(struct D_surface *__surface);

/**
 * \brief Prepares __surface for rendering.
 *
 * \param __surface Specifies the surface to be prepared.
 */
void
D_prepare_surface_for_rendering(struct D_surface *__surface);

/**
 * \brief Sets surface's uv shift.
 *
 * \param __surface Specifies the surface whose uv will be setted.
 * \param __row     Specifies the row to begin the uv with.
 * \param __column  Specifies the column to begin te uv with.
 * \param __padding Specifies the space to be ignored starting from the borders.
 */
void
D_set_surface_uv_shift(struct D_surface *__surface,
                       unsigned int      __column,
                       unsigned int      __row,
                       vec2              __padding);

/**
 * \brief Sets surface's position
 *
 * \param __surface  Specifies the surface whose position will be setted.
 * \param __position Specifies the new position.
 */
void
D_set_surface_position(struct D_surface *__surface,
                       vec2              __position);

/**
 * \brief Translates the surface.
 *
 * \param __surface     Specifies the surface to be translated.
 * \param __translation Specifies the vector to translate the surface with.
 */
void
D_translate_surface(struct D_surface *__surface,
                    vec2              __translation);

/**
 * \brief Sets the surface's rotation.
 *
 * \param __surface  Specifies the surface to be rotated.
 * \param __rotation Specifies the new rotation.
 */
void
D_set_surface_rotation(struct D_surface *__surface,
                       float             __rotation);

/**
 * \brief Rotates the surface.
 *
 * \param __surface  Specifies the surface to be rotated.
 * \param __rotation Specifies the value to rotate the surface with.
 */
void
D_rotate_surface(struct D_surface *__surface,
                 float             __rotation);

/**
 * \brief Sets the surface's scale.
 *
 * \param __surface Specifies the surface to be scaled.
 * \param __scale   Specifies the new scale.
 */
void
D_set_surface_scale(struct D_surface *__surface,
                    vec2             __scale);

/**
 * \brief Scales the surface.
 *
 * \param __surface Specifies the surface to be scaled.
 * \param __scale   Specifies the vector to scale the surface with.
 */
void
D_scale_surface(struct D_surface *__surface,
                vec2              __scale);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_SURFACE_H__ */
