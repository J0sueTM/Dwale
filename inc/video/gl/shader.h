/**
 * \file inc/video/gl/shader.h
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date May 02, 2021
 *
 * \brief Vertex Shader related functionalities
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

struct D_shader
{
  u32 vertex_shader_handle,
      fragment_shader_handle,
      shader_program_handle;
};

struct D_shader *
D_create_shader(char *__vertex_shader_file,
                char *__fragment_shader_file);

struct D_shader *
D_create_shader_from_string(const char *__vertex_shader_source,
                            const char *__fragment_shader_source);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_SHADER_H__ */
