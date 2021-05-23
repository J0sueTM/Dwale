/**
 * \file inc/core/types.h
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \data April 21, 2021
 *
 * \brief Cross platform typedefs
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

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#ifndef __D_TYPES_H__
#define __D_TYPES_H__

#include "core/core.h"

#ifdef _WIN32
#ifdef __D_ARCH64__
  typedef unsigned __int64 u64;
  typedef          __int64 i64;
#endif /* D_ARCH64__*/
  typedef unsigned __int32 u32;
  typedef          __int32 i32;
  typedef unsigned __int16 u16;
  typedef          __int16 i16;
  typedef unsigned __int8  u8;
  typedef          __int8  i8;
#else
#ifdef __D_ARCH64__
  typedef u_int64_t u64;
  typedef int64_t   i64;
#endif /* __D_ARCH64__ */
  typedef u_int32_t u32;
  typedef int32_t   i32;
  typedef u_int16_t u16;
  typedef int16_t   i16;
  typedef u_int8_t  u8;
  typedef int8_t    i8;
#endif /* _WIN32 */
typedef float  f32;
typedef double f64;
typedef long double f128;

#define D_DISABLED 0x00
#define D_ENABLED 0X01

#endif /* __D_TYPES_H__ */

#ifdef __cplusplus
}
#endif /* __cplusplus */
