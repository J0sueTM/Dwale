/**
 * \file src/video/gl/texture.h
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date May 16, 2021
 *
 * \brief Texture related functionalities
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

#include "video/gl/texture.h"

struct D_texture *
D_create_texture(char *__file_name,
                 u32   __type,
                 u32   __wrap_s,
                 u32   __wrap_t,
                 u32   __filter_s,
                 u32   __filter_t,
                 u32   __format)
{
  if (!__file_name)
  {
    D_raise_error(DERR_NOPARAM("__file_name", "File name can't be NULL"));

    return NULL;
  }
  
  struct D_texture *new_texture = (struct D_texture *)malloc(sizeof(struct D_texture));
  D_assert(new_texture, NULL);
  new_texture->type = __type;

  glGenTextures(1, &new_texture->handle);
  D_bind_texture(new_texture);
  glTexParameteri(__type, GL_TEXTURE_WRAP_S, __wrap_s);
  glTexParameteri(__type, GL_TEXTURE_WRAP_T, __wrap_t);
  glTexParameteri(__type, GL_TEXTURE_MIN_FILTER, __filter_s);
  glTexParameteri(__type, GL_TEXTURE_MIN_FILTER, __filter_t);

  /* opengl expects the pixel data to be reversed. */
  stbi_set_flip_vertically_on_load(true);
  u8 *texture_image_data = stbi_load(__file_name, &new_texture->width, &new_texture->height, &new_texture->nr_channels, 0);
  if (!texture_image_data)
  {
    D_raise_error("Could not load texture image");

    return NULL;
  }

  if (__type == GL_TEXTURE_1D ||
      __type == GL_PROXY_TEXTURE_1D)
  { glTexImage1D(__type, 0, __format, new_texture->width, 0, __format, GL_UNSIGNED_BYTE, texture_image_data); }
  else
  { glTexImage2D(__type, 0, __format, new_texture->width, new_texture->height, 0, __format, GL_UNSIGNED_BYTE, texture_image_data); }
  glGenerateMipmap(__type);
  stbi_image_free(texture_image_data);

  D_raise_log("Created texture");
  return new_texture;
}

void
D_end_texture(struct D_texture *__texture)
{
  if (!__texture)
  {
    D_raise_error(DERR_NOPARAM("__texture", "Texture can't be NULL and/or wasn't initialized"));

    return;
  }

  free(__texture);
  D_raise_log("Ended texture");
}

void
D_bind_texture(struct D_texture *__texture)
{
  if (!__texture)
  {
    D_raise_error(DERR_NOPARAM("__texturre", "Texture can't be NULL and/or wasn't initialized"));

    return;
  }

  glBindTexture(__texture->type, __texture->handle);
}
