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
D_create_camera(unsigned int     __projection_type,
                struct D_window *__window,
                float            __fovy,
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
  new_camera->projection_type = __projection_type;
  new_camera->window = __window;
  new_camera->fovy = __fovy;
  new_camera->near_clip = __near_clip;
  new_camera->far_clip = __far_clip;

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
}
