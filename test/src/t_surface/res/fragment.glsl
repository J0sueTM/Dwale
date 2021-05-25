/**
 * \file test/src/t_surface/res/fragment.glsl
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date May 22, 2021
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

in vec2 vo_tex_coord;
in vec3 vo_color;

uniform sampler2D u_texture_tux;
uniform sampler2D u_texture_gnu;

void
main()
{
  /*
  FragColor = mix(texture(u_texture_tux, vo_tex_coord), texture(u_texture_gnu, vo_tex_coord), 0.3f) * vec4(vo_color, 1.0f);
  */
  gl_FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
