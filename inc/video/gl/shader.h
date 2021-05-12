/**
 * \file inc/video/gl/shader.h
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date May 02, 2021
 *
 * \brief Vertex/Fragment Shader related functionalities
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

typedef u32 D_shader;
typedef u32 D_program;

struct D_shaders
{
  D_shader  vertex_shader, fragment_shader;
  const char *vertex_shader_source, *fragment_shader_source;
  D_program program;
};

D_shader
D_create_shader(u32         __type,
                const char *__shader_source);

struct D_shaders *
D_create_shaders(const char *__vertex_shader_source,
                 const char *__fragment_shader_source);

void
D_end_shaders(struct D_shaders *__shaders);

struct D_shaders *
D_create_shaders_from_file(char *__vertex_shader_source_file_name,
                           char *__fragment_shader_source_file_name);

void
D_apply_shaders(struct D_shaders *__shaders);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_SHADER_H__ */
