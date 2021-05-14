/**
 * \file inc/util/vector2.h
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date April 23, 2021
 *
 * \brief Bidimensional vector related functionalities
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

#ifndef __D_VECTOR2_H__
#define __D_VECTOR2_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "core/core.h"
#include <math.h>

struct D_u32vector2
{
  u32 x;
  u32 y;
};

struct D_i32vector2
{
  i32 x;
  i32 y;
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_VECTOR2_H__ */
