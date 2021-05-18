/**
 * \file test/src/t_texture/res/fragment_shader.glsl
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date May 16, 2021
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

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D u_texture_city;
uniform sampler2D u_texture_tux;

void
main()
{ FragColor = mix(texture(u_texture_city, TexCoord), texture(u_texture_tux, TexCoord), 0.2f); }
