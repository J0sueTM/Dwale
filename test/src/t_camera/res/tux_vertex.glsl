/**
 * \file test/src/t_camera/res/tux_vertex.glsl
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date Jun 18, 2021
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
layout (location = 1) in vec2 l_uv;

out vec2 vo_uv;

uniform mat4 u_mvp;
uniform vec2 u_uv_shift;

void
main()
{
  gl_Position = u_mvp * vec4(l_pos, 1.0f);
  vo_uv = l_uv + u_uv_shift;
}
