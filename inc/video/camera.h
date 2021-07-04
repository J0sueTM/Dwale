/**
 * \file inc/video/camera.h
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date May 28, 2021
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
 
#ifndef __D_CAMERA_H__
#define __D_CAMERA_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "core/core.h"
#include "video/window.h"
#include "cglm/vec2.h"
#include "cglm/mat4.h"
#include "cglm/cam.h"
#include "cglm/affine.h"

struct D_camera
{
  vec3 position, scale;
  float rotation;
  
  mat4 view, projection, mvp;
  float near_clip, far_clip;
  struct D_window *window;
};

/**
 * \brief Creates a new camera.
 *
 * \param __window          Specifies the window in which the camera should work.
 * \param __near_clip       Specifies the near clip cut.
 * \param __far_clip        Specifies the far clip cut.
 *
 * \return the created camera.
 */
struct D_camera *
D_create_camera(struct D_window *__window,
                float            __near_clip,
                float            __far_clip);

/**
 * \brief Ends given camera.
 *
 * \param __camera Specifies the camera to be ended.
 */
void
D_end_camera(struct D_camera *__camera);

/**
 * \brief Resets camera's matrices (view and projection).
 *
 * \param __camera Specifies the camera to be reseted.
 */
void
D_reset_camera(struct D_camera *__camera);

/**
 * \brief Sets the camera's position.
 *
 * \param __camera   Specifies the camera whose position will be setted.
 * \param __position Specifies the new position.
 */
void
D_set_camera_position(struct D_camera *__camera,
                      vec2             __position);

/**
 * \brief Translates the camera's view.
 *
 * \param __camera      Specifies the camera whose view will be translated.
 * \param __translation Specifies the translation to be used with the camera.
 */
void
D_translate_camera(struct D_camera *__camera,
                   vec2             __translation);

/**
 * \brief Sets the camera's rotation.
 *
 * \param __camera   Specifies the camera whose rotation will be setted.
 * \param __rotation Specifies the new rotation.
 */
void
D_set_camera_rotation(struct D_camera *__camera,
                      float            __rotation);

/**
 * \brief Rotates the camera's view.
 *
 * \param __camera   Specifies the camera whose view will be rotated.
 * \param __rotation Specifies the rotation to be used to rotate the camera.
 */
void
D_rotate_camera(struct D_camera *__camera,
                float            __rotation);

/**
 * \brief Sets the camera's scale.
 *
 * \param __camera Specifies the camera whose scale will be setted.
 * \param __scale  Specifies the new scale.
 */
void
D_set_camera_scale(struct D_camera *__camera,
                   vec2             __scale);

/**
 * \brief Scales the camera's view.
 *
 * \param __camera Specifies the camera whose view will be scaled.
 * \param __scale  Specifies the scale to be used to scale the camera.
 */
void
D_scale_camera(struct D_camera *__camera,
               vec2             __scale);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_CAMERA_H__ */
