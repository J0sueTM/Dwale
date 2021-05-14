/**
 * \file inc/video/gl/shader.h
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date May 02, 2021
 *
 * \brief GL shaders related functionalities
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

#ifndef __D_SHADER_H__
#define __D_SHADER_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "core/core.h"
#include "video/video.h"

/* TODO(J0sueTM): Add geometry shader */

struct D_shaders
{
  u32 vertex_shader,
      fragment_shader,
      program;
};

/**
 * \brief Creates an opengl shader according to __type
 *
 * \param __type          Specifies the shader type, whether vertex or fragment.
 * \param __shader_source Specifies a C null terminated string containing a GLSL code for the shader.
 *
 * \return The created buffer's gpu buffer
 */
u32
D_create_shader(u32         __type,
                const char *__shader_source);

/**
 * \brief Creates both vertex and fragment shaders on a D_shaders structure
 *
 * \param __vertex_shader_source   Specifies a C null terminated string containing a GLSL code for the vertex shader.
 * \param __fragment_shader_source Specifies a C null terminated string containing a GLSL code for the fragment shader.
 *
 * \return The D_shaders structure containing the shaders' buffer and their source code.
 *
 * NOTE(All): The source code points to the given params. So, freeing the given source code may block dwale's ability on debugging.
 */
struct D_shaders *
D_create_shaders(const char *__vertex_shader_source,
                 const char *__fragment_shader_source);

/**
 * \brief Ends given shaders buffers and frees it's source codes (if not freed yet).
 *
 * \param __shaders Specifies the shaders structure to be ended.
 */
void
D_end_shaders(struct D_shaders *__shaders);

/**
 * \brief Copies given files content (which should be GLSL code) to C strings and calls D_create_shaders.
 *
 * \param __vertex_shader_source_file_name   Specifies the file name of the vertex shader's source code.
 * \param __fragment_shader_source_file_name Specifies the file name of the fragment shader's source code.
 *
 * \return Created shaders structure, which should be returned from D_create_shaders.
 *
 * \see D_create_shaders
 */
struct D_shaders *
D_create_shaders_from_file(char *__vertex_shader_source_file_name,
                           char *__fragment_shader_source_file_name);

void
D_apply_shaders(struct D_shaders *__shaders);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_SHADER_H__ */
