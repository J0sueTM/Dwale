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
#include "cglm/vec2.h"
#include "cglm/vec3.h"
#include "cglm/vec4.h"
#include "cglm/mat2.h"
#include "cglm/mat3.h"
#include "cglm/mat4.h"

/* TODO(J0sueTM): Add geometry shader */

struct D_shaders
{
  unsigned int vertex_shader, fragment_shader, program;
};

/**
 * \brief Creates an opengl shader according to __type
 *
 * \param __type          Specifies the shader type, whether vertex or fragment.
 * \param __shader_source Specifies a C null terminated string containing a GLSL code for the shader.
 *
 * \return The created buffer's gpu buffer
 */
unsigned int
D_create_shader(unsigned int  __type,
                const char   *__shader_source);

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

/**
 * \brief Applies given shader.
 *
 * \param __shaders Specifies the shaders to be applied.
 */
void
D_apply_shaders(struct D_shaders *__shaders);

 /**
 * \brief Sets an integer uniform to shaders.
 *
 * \param __shaders Specifies the shaders that expects the uniform.
 * \param __value   Specifies the integer to be setted.
 * \param __name    Specifies the string that the shaders expects.
 */
void
D_set_uniform_int(struct D_shaders *__shaders,
                  int               __value,
                  char             *__name);

/**
 * \brief Sets a float uniform to shaders.
 *
 * \param __shaders Specifies the shaders that expects the uniform.
 * \param __value   Specifies the integer to be setted.
 * \param __name    Specifies the string that the shaders expects.
 */  
void
D_set_uniform_float(struct D_shaders *__shaders,
                   float              __value,
                   char              *__name);

/**
 * \brief Sets a boolean uniform to shaders.
 *
 * \param __shaders Specifies the shaders that expects the uniform.
 * \param __value   Specifies the integer to be setted.
 * \param __name    Specifies the string that the shaders expects.
 */
void
D_set_uniform_bool(struct D_shaders *__shaders,
                   bool              __value,
                   char             *__name);

/**
 * \brief Sets a vec4 uniform to shaders.
 *
 * \param __shaders Specifies the shaders that expects the uniform.
 * \param __value   Specifies the integer to be setted.
 * \param __name    Specifies the string that the shaders expects.
 */
void
D_set_uniform_vec4(struct D_shaders *__shaders,
                   vec4              __value,
                   char             *__name);

/**
 * \brief Sets a vec3 uniform to shaders.
 *
 * \param __shaders Specifies the shaders that expects the uniform.
 * \param __value   Specifies the integer to be setted.
 * \param __name    Specifies the string that the shaders expects.
 */
void
D_set_uniform_vec3(struct D_shaders *__shaders,
                   vec3              __value,
                   char             *__name);

/**
 * \brief Sets a vec2 uniform to shaders.
 *
 * \param __shaders Specifies the shaders that expects the uniform.
 * \param __value   Specifies the integer to be setted.
 * \param __name    Specifies the string that the shaders expects.
 */
void
D_set_uniform_vec2(struct D_shaders *__shaders,
                   vec2              __value,
                   char             *__name);

/**
 * \brief Sets a mat4 uniform to shaders.
 *
 * \param __shaders Specifies the shaders that expects the uniform.
 * \param __value   Specifies the integer to be setted.
 * \param __name    Specifies the string that the shaders expects.
 */
void
D_set_uniform_mat4(struct D_shaders *__shaders,
                   mat4              __value,
                   char             *__name);

/**
 * \brief Sets a mat3 uniform to shaders.
 *
 * \param __shaders Specifies the shaders that expects the uniform.
 * \param __value   Specifies the integer to be setted.
 * \param __name    Specifies the string that the shaders expects.
 */
void
D_set_uniform_mat3(struct D_shaders *__shaders,
                   mat3              __value,
                   char             *__name);

/**
 * \brief Sets a mat2 uniform to shaders.
 *
 * \param __shaders Specifies the shaders that expects the uniform.
 * \param __value   Specifies the integer to be setted.
 * \param __name    Specifies the string that the shaders expects.
 */
void
D_set_uniform_mat2(struct D_shaders *__shaders,
                   mat2              __value,
                   char             *__name);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_SHADER_H__ */
