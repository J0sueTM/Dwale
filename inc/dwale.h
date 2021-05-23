/**
 * \file inc/dwale.h
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date April 22, 2021
 *
 * \brief Base includes for dwale
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

#ifndef __D_H__
#define __D_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#ifndef __D_INCLUDE_NONE__
  
#include "core/core.h"

#include "cglm/vec2.h"
#include "cglm/vec3.h"
#include "cglm/vec4.h"
#include "cglm/affine.h"

#include "video/video.h"
#include "video/window.h"

#include "video/gl/gl_object.h"
#include "video/gl/shader.h"
#include "video/gl/texture.h"

#include "video/surface.h"
#include "video/renderer.h"
  
#endif /* __D_INCLUDE_NONE__ */

/**
 * \brief Initialises dwale and it's dependencies
 */
void
D_init();

/**
 * \brief Ends dwale and it's dependencies
 */
void
D_end();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_H__ */
