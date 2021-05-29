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

#define D_GLSL_VERSION "#version 330 core\n"
#define D_GLSL_MAINBEG \
  "void\n" \
  "main()\n" \
  "{\n"
#define D_GLSL_MAINEND "}\n"

#define D_GLSL_LAYOUT0 "layout (location = 0) = in vec3 l_pos;\n"
#define D_GLSL_LAYOUT1 "layout (location = 1) = in vec2 l_color;\n"
#define D_GLSL_LAYOUT2 "layout (location = 2) = in vec2 l_tex_coord;\n"

#define D_GLSL_UNIFORMMODEL "uniform mat4 u_mat_model;\n"
#define D_GLSL_UNIFORMVIEW  "uniform mat4 u_mat_view;\n"
#define D_GLSL_UNIFORMPROJ  "uniform mat4 u_mat_projection;\n"

#define D_GLSL_POS "  gl_Position = vec4(l_pos, 1.0f);\n"

/* glm vectors and matrices */
#define D_GLSL_FRAG(__color) \
  "  gl_FragColor = vec4(" \
  __color.x ", " \
  __color.y ", " \
  __color.z ", " \
  __color.w ");\n"
#define D_GLSL_FRAGT(__texture_name, __texture_coords) \
  "  gl_FragColor = texture(" \
  __texture_name ", " \
  __texture_coords ");\n"
#define D_GLSL_FRAGTC(__texture_name, __texture_coords, __color) \
  "  gl_FragColor = texture(" \
  __texture_name ", " \
  __texture_coords ")" \
  " * vec4(" \
  __color.x ", " \
  __color.y ", " \
  __color.z ", " \
  __color.w ");\n"\

/* shader's vectors and matrices */
#define D_GLSL_FRAGIN "  gl_FragColor = vec4(vo_color, 1.0f);\n"
#define D_GLSL_FRAGTIN(__texture_name) \
  "  gl_FragColor = texture(" \
  __texture_name, \
  "vo_tex_coord;\n" \
  ");\n"
#define D_GLSL_FRAGTCIN(__texture_name) \
  "  gl_FragColor = texture(" \
  __texture_name, \
  "vo_tex_coord)" \
  " * vec4(vo_color, 1.0f);\n"
  
#define D_vertex_simple \
  D_GLSL_VERSION \
  D_GLSL_UNIFORM0 \
  D_GLSL_MAINBEG \
  D_GLSL_POS \
  D_GLSL_MAINEND \
  '\0'

#define D_fragment_simple(__color) \
  D_GLSL_VERSION \
  D_GLSL_UNIFORM0 \
  D_GLSL_MAINBEG \
  D_GLSL_FRAG(__color) \
  D_GLSL_MAINEND \
  '\0'

#define D_vertex_simple_layouts \
  D_GLSL_VERSION \
  D_GLSL_UNIFORM0 \
  D_GLSL_UNIFORM1 \
  "out vec3 vo_color;\n" \
  D_GLSL_MAINBEG \
  D_GLSL_POS \
  "  vo_color = l_color;\n" \
  D_GLSL_MAINEND \
  '\0'

#define D_fragment_simple_layouts \
  D_GLSL_VERSION \
  "in vec3 vo_color;" \
  D_GLSL_MAINBEG \
  D_GLSL_FRAGIN \
  D_GLSL_MAINEND \
  '\0'

#define D_vertex_all_layouts \
  D_GLSL_VERSION \
  D_GLSL_UNIFORM0 \
  D_GLSL_UNIFORM1 \
  D_GLSL_UNIFORM2 \
  D_GLSL_UNIFORM3 \
  "out vec3 vo_color;\n" \
  "out vec2 vo_tex_coord;\n" \
  D_GLSL_MAINBEG \
  D_GLSL_POS \
  "  vo_color = l_color;\n" \
  "  vo_tex_coord = l_tex_coord;" \
  D_GLSL_MAINEND \
  '\0'

#define D_fragment_all_layouts(__texture_name) \
  D_GLSL_VERSION \
  "in vec3 vo_color;\n" \
  "in vec2 vo_tex_coord;\n" \
  D_GLSL_MAINBEG \
  D_GLSL_FRAGTCIN(__texture_name) \
  D_GLSL_MAINEND \
  '\0'

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_DEFAULT_SHADERS_H__ */
