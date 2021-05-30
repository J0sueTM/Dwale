/**
 * \file inc/video/default_shaders.h
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date May 29, 2021
 *
 * \brief Default shaders
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

#ifndef __D_DEFAULT_SHADERS_H__
#define __D_DEFAULT_SHADERS_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#define D_VERTEX_SIMPLE \
  "#version 330 core\n" \
  "layout (location = 0) in vec3 l_pos;\n" \
  "void main() {\n" \
  "gl_Position = vec4(l_pos, 1.0f);\n" \
  "}"
#define D_FRAGMENT_SIMPLE(__color) \
  "#version 330 core\n" \
  "void main() {\n" \
  "gl_FragColor = " \
  "vec4(" \
  __color.x ", " \
  __color.y ", " \
  __color.z ", " \
  __color.w ");\n" \
  "}"

#define D_VERTEX_SIMPLE_MVP \
  "#version 330 core\n" \
  "layout (location = 0) in vec3 l_pos;\n" \
  "uniform mat4 u_model;\n" \
  "uniform mat4 u_view;\n" \
  "uniform mat4 u_projection;\n" \
  "void main() {\n" \
  "gl_Position = u_projection * u_view * u_model * vec4(l_pos, 1.0f);\n" \
  "}"
#define D_FRAGMENT_SIMPLE_MVP(__color) \
  D_FRAGMENT_SIMPLE(__color)

#define D_VERTEX_SIMPLE_LAYOUTS \
  "#version 330 core\n" \
  "layout (location = 0) in vec3 l_pos;\n" \
  "layout (location = 1) in vec3 l_color;\n" \
  "out vec3 vo_color;\n" \
  "void main() {\n" \
  "gl_Position = vec4(l_pos, 1.0f);\n" \
  "vo_color = l_color;\n" \
  "}"
#define D_FRAGMENT_SIMPLE_LAYOUTS \
  "#version 330 core\n" \
  "in vec3 vo_color;\n" \
  "void main() {\n" \
  "gl_FragColor = vec4(vo_color, 1.0f);\n" \
  "}"

#define D_VERTEX_SIMPLE_LAYOUTS_MVP \
  "#version 330 core\n" \
  "layout (location = 0) in vec3 l_pos;\n" \
  "layout (location = 1) in vec3 l_color;\n" \
  "out vec3 vo_color;\n" \
  "uniform mat4 u_model;\n" \
  "uniform mat4 u_view;\n" \
  "uniform mat4 u_projection;\n" \
  "void main() {\n" \
  "gl_Position = u_projection * u_view * u_model * vec4(l_pos, 1.0f);\n" \
  "vo_color = l_color;\n" \
  "}"
#define D_FRAGMENT_SIMPLE_LAYOUTS_MVP \
  D_FRAGMENT_SIMPLE_LAYOUTS

#define D_VERTEX_ALL_LAYOUTS \
  "#version 330 core\n" \
  "layout (location = 0) in vec3 l_pos;\n" \
  "layout (location = 1) in vec3 l_color;\n" \
  "layout (location = 2) in vec2 l_texture_coord;\n" \
  "out vec3 vo_color;\n" \
  "out vec2 vo_texture_coord;\n" \
  "void main() {\n" \
  "gl_Position = vec4(l_pos, 1.0f);\n" \
  "}"

#define D_FRAGMENT_ALL_LAYOUTS(__texture_name) \
  "#version 330 core\n" \
  "in vec3 vo_color;\n" \
  "in vec2 vo_texture_coord;\n" \
  "uniform sampler2D " __texture_name ";\n" \
  "void main() {\n" \
  "gl_FragColor = texture(" __texture_name ", vo_texture_coord); * vec4(vo_color, 1.0f);\n" \
  "}"

#define D_VERTEX_ALL_LAYOUTS_MVP \
  "#version 330 core" \
  "layout (location = 0) in vec3 l_pos;\n" \
  "layout (location = 1) in vec3 l_color;\n" \
  "layout (location = 2) in vec3 l_texture_coord;\n" \
  "out vec3 vo_color;\n" \
  "out vec2 vo_texture_coord;\n" \
  "uniform mat4 u_model;\n" \
  "uniform mat4 u_view;\n" \
  "uniform mat4 u_projection;\n" \
  "void main() {\n" \
  "gl_Position = u_projection * u_view * u_model * vec4(l_pos, 1.0f);\n" \
  "}"
#define D_FRAGMENT_ALL_LAYOUTS_MVP(__texture_name) \
  D_FRAGMENT_ALL_LAYOUTS(__texture_name)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_DEFAULT_SHADERS_H__ */
