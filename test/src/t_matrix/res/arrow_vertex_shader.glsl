/**
 * \file test/src/t_matrix/res/arrow_vertex_shader.glsl
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date May 20, 2021
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

#version 330 core

layout (location = 0) in vec3 l_pos;
layout (location = 1) in vec3 l_tex_coord;

out vec2 ov_tex_coord;

uniform mat4 u_transform_arrow;

void
main()
{
  gl_Position = vec4(l_pos, 1.0f) * u_transform_arrow;
  ov_tex_coord = vec2(l_tex_coord.x, l_tex_coord.y);
}
