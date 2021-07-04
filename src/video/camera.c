/**
 * \file src/video/camera.c
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date May 29, 2021
 *
 * \brief Camera and view utilities
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

#include "video/camera.h"

struct D_camera *
D_create_camera(struct D_window *__window,
                float            __near_clip,
                float            __far_clip)
{
  if (!__window)
  {
    D_raise_error(DERR_NOPARAM("__window", "Window can't be NULL"));

    return NULL;
  }
  else if (!__window)
  {
    D_raise_error(DERR_NOPARAM("__window", "Camera can't be NULL"));

    return NULL;
  }

  struct D_camera *new_camera = (struct D_camera *)malloc(sizeof(struct D_camera));
  D_assert(new_camera, NULL);
  new_camera->window = __window;
  new_camera->near_clip = __near_clip;
  new_camera->far_clip = __far_clip;

  new_camera->rotation = 0.0f;
  glm_vec3_zero(new_camera->position);
  glm_vec3_one(new_camera->scale);

  D_reset_camera(new_camera);

  D_raise_log("Created camera");
  return new_camera;
}

void
D_end_camera(struct D_camera *__camera)
{
  if (!__camera)
  {
    D_raise_error(DERR_NOPARAM("__camera", "camera can't be NULL"));

    return;
  }

  free(__camera);
  D_raise_log("Ended camera");
}

void
D_reset_camera(struct D_camera *__camera)
{
  if (!__camera)
  {
    D_raise_error(DERR_NOPARAM("__camera", "Camera can't be NULL"));

    return;
  }

  glm_mat4_identity(__camera->view);
  glm_translate(__camera->view, __camera->position);
  glm_rotate(__camera->view, __camera->rotation, (vec3){ 0.0f, 0.0f, 1.0f });
  glm_scale(__camera->view, __camera->scale);
  
  glm_mat4_identity(__camera->projection);
  glm_ortho(-__camera->window->view_proportion[0] / __camera->window->view_proportion[1],
            __camera->window->view_proportion[0] / __camera->window->view_proportion[1],
            -1.0f, 1.0f, __camera->near_clip, __camera->far_clip, __camera->projection);
}

void
D_set_camera_position(struct D_camera *__camera,
                      vec2             __position)
{
  if (!__camera)
    return;

  __camera->position[0] = __position[0];
  __camera->position[1] = __position[0];
}

void
D_translate_camera(struct D_camera *__camera,
                   vec2             __translation)
{
  if (!__camera)
    return;

  __camera->position[0] -= __translation[0];
  __camera->position[1] -= __translation[1];
}

void
D_set_camera_rotation(struct D_camera *__camera,
                      float            __rotation)
{
  if (!__camera)
    return;

  __camera->rotation = __rotation;
}

void
D_rotate_camera(struct D_camera *__camera,
                float            __rotation)
{
  if (!__camera)
    return;

  __camera->rotation += (__rotation);
}

void
D_set_camera_scale(struct D_camera *__camera,
                   vec2             __scale)
{
  if (!__camera)
    return;

  __camera->scale[0] = __scale[0];
  __camera->scale[1] = __scale[1];
}

void
D_scale_camera(struct D_camera *__camera,
               vec2             __scale)
{
  if (!__camera)
    return;

  __camera->scale[0] *= __scale[0];
  __camera->scale[1] *= __scale[1];
}
