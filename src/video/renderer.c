/**
 * \file inc/video/renderer.h
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date May 14, 2021
 *
 * \brief Renderer related functionalities
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

#include "video/renderer.h"

void
D_draw_arrays(struct D_vao     *__vao,
              struct D_vbo     *__vbo,
              struct D_shaders *__shaders)
{
  if (!__vao)
  {
    D_raise_error(DERR_NOPARAM("__vao", "Vertex array object can't be null and/or wasn't initialized"));

    return;
  }
  else if (!__vbo)
  {
    D_raise_error(DERR_NOPARAM("__vbo", "Vertex buffer object can't be null and/or wasn't initialized"));
    
    return;
  }

  if (__shaders)
  { D_apply_shaders(__shaders); }

  D_bind_vao(__vao);
  glDrawArrays(__vbo->draw_type, 0, 3);
#ifdef __D_DEBUG__
    D_unbind_vao();
#endif /* __D_DEBUG__ */
}

void
D_draw_elements(struct D_vao     *__vao,
                struct D_vbo     *__ebo,
                u32               __count,
                u32               __type,
                struct D_shaders *__shaders)
{
  if (!__vao)
  {
    D_raise_error(DERR_NOPARAM("__vao", "Vertex array object can't be null and/or wasn't initialized"));

    return;
  }
  else if (!__ebo)
  {
    D_raise_error(DERR_NOPARAM("__ebo", "Element array buffer object can't be null and/or wasn't initialized"));
    
    return;
  }

  if (__shaders)
  { D_apply_shaders(__shaders); }

  D_bind_vao(__vao);
  glDrawElements(__ebo->draw_type, __count, __type, 0);

#ifdef __D_DEBUG__
  D_unbind_vao();
#endif /* __D_DEBUG__ */
}
