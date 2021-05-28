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

#include "core/core.h"
#include "video/video.h"
#include "video/gl/shader.h"
#include "video/gl/texture.h"
#include "video/gl/gl_object.h"
#include "cglm/vec2.h"
#include <math.h>

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
  int id;
  struct D_texture *texture;
  struct D_texture_node *next;
  struct D_texture_node *prev;
};

struct D_surface
{
  struct D_transformation
  {
    vec3 position, rotation, scale;
  } transformation;
  
  float *vct;       /* vertices, colors and texture coordinates */
  unsigned int *vi; /* vertices indices (EBO) */
  
  struct D_vao *vao;
  struct D_vbo *vbo;
  struct D_vbo *ebo;

  struct D_shaders *shaders;  

  /*
   * NOTE(all): Since rendering works as a layer of all rendering contexts,
   * textures are stacked(linked) into this implementation of linked list.
   *
   * For performance reasons, it will be faster to begin iterating from the tail
   * if the node is closer to it rather than to the head.
   */
  struct D_texture_node *head_texture_node;
  struct D_texture_node *tail_texture_node;
  unsigned int ebo_count, ebo_type;
};

/**
 * \brief Creates a new surface.
 *
 * \param __vct_size  Specifies the size of __vct.
 * \param __vct       Specifies the vertex color texture coordinates vertex.
 * \param __vi_size   Specifies the size of __vi.
 * \param __vi        Specifies the indices of __vct.
 *                    NOTE(all): If your surface should not have an ebo, pass __vi as NULL,
 *                    Dwale will get it as a vertex array object and render it as a vertex array object.
 * \param __stride    Specifies the stride from one vertex and the beggining of it's precedent.
 *                    In case of a 3x3x2, the stride should be 8.
 * \param __draw_type Specifies the draw type of the vbo.
 * \param __draw_mode Specifies the draw mode of the vbo.
 * \param __ebo_count Specifies the amount of indices in you __vi. If you passed __vi as NULL, this will be ignored.
 * \param __ebo_type  Specifies the type of data in __vi. If you passed __vi as NULL, this will be ignored.
 * \param __shaders   Specifies the shaders to be run when rendering the surface.
 *
 * \return The created surface.
 */
struct D_surface *
D_create_surface(unsigned int       __vct_size,
                 float             *__vct,
                 unsigned int       __vi_size,
                 unsigned int      *__vi,
                 unsigned int       __stride,
                 unsigned int       __draw_type,
                 unsigned int       __draw_mode,
                 unsigned int       __ebo_count,
                 unsigned int       __ebo_type,
                 struct D_shaders *__shaders);

/**
 * \brief Ends the surface. Frees memory and dependencies.
 */
void
D_end_surface(struct D_surface *__surface);

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

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_SURFACE_H__ */
