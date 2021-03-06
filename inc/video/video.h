/**
 * \file inc/video/video.h
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date April 22, 2021
 *
 * \brief Visual related utilities
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

#ifndef __D_VIDEO_H__
#define __D_VIDEO_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "core/core.h"
#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

/*
 * I'm sure you'll hardly reach this amount in a single shader.
 * In any case, just change it and make sure the GPU supports the new value.
 */
#define D_MAX_TEXTURES_ON_SURFACE 16

/**
 * \brief Initialises dwale's video related dependencies.
 */  
void
D_init_video();

/**
 * \brief Initialises video dependencies that can't be initialised in D_init_video
 */
void
D_post_init_video();

/**
 * \brief Ends dwale's video related dependencies.
 */
void
D_end_video();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_VIDEO_H__ */
