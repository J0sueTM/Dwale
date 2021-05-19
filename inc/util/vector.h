/**
 * \file inc/util/vector.h
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date April 23, 2021
 *
 * \brief Vector related functionalities
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

#ifndef __D_VECTOR_H__
#define __D_VECTOR_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "core/core.h"
#include <math.h>

/* 64 */
#ifdef __D_ARCH64__
struct u64vec4
{ u64 x, y, z, w; };

struct i64vec4
{ i64 x, y, z, w; };

struct f64vec4
{ f64 x, y, z, w; };

struct u64vec3
{ u64 x, y, z; };

struct i64vec3
{ i64 x, y, z; };

struct f64vec3
{ f64 x, y, z; };

struct u64vec2
{ u64 x, y; };

struct i64vec2
{ i64 x, y; };

struct f64vec2
{ f64 x, y; };
#endif /* __D_ARCH64__ */

/* 32 */
struct u32vec4
{ u32 x, y, z, w; };

struct i32vec4
{ i32 x, y, z, w; };

struct f32vec4
{ f32 x, y, z, w; };

struct u32vec3
{ u32 x, y, z; };

struct i32vec3
{ i32 x, y, z; };

struct f32vec3
{ u32 x, y, z; };

struct u32vec2
{ u32 x, y; };

struct i32vec2
{ i32 x, y; };

struct f32vec2
{ f32 x, y; };

/* 16 */
struct u16vec4
{ u16 x, y, z, w; };

struct i16vec4
{ i16 x, y, z, w; };

struct u16vec3
{ u16 x, y, z; };

struct i16vec3
{ i16 x, y, z; };

struct u16vec2
{ u16 x, y; };

struct i16vec2
{ i16 x, y; };

/* 8 */
struct u8vec4
{ u8 x, y, z, w; };

struct i8vec4
{ i8 x, y, z, w; };

struct u8vec3
{ u8 x, y, z; };

struct i8vec3
{ i8 x, y, z; };

struct u8vec2
{ u8 x, y; };

struct i8vec2
{ i8 x, y; };

#define D_check_vectors2(__l, \
                         __r) \
  sizeof(*__l) == sizeof(*__r)
#define D_check_vectors3(__l, \
                         __r, \
                         __v) \
  sizeof(*__l) == sizeof(*__r) && sizeof(*__l) == sizeof(*__v)

#define D_add_vector(__l, \
                     __r) \
{ \
  if (!D_check_vectors2(__l, __r)) \
  { D_raise_error(DERR_VECS2); } \
  else \
  { \
    /* Iterates through the struct's members  */ \
    for (i32 i = 0; i < (sizeof(*__l) / sizeof((*__l).x)); ++i) \
    { *(__l.x + i) += *(__r.x + i); } \
  } \
}

#define D_add_vector_to(__l, \
                        __r, \
                        __v) \
{ \
  /* Iterates through the struct's members  */ \
  for (i32 i = 0; i < (sizeof(*__l) / sizeof((*__l).x)); ++i) \
  { *(__v.x + i) = *(__l.x + i) + *(__r.x + i); } \
}

#define D_sub_vector(__l, \
                     __r) \
{ \
  if (!D_check_vectors2(__l, __r)) \
  { D_raise_error(DERR_VECS2); } \
  else \
  { \
    /* Iterates through the struct's members  */ \
    for (i32 i = 0; i < (sizeof(*__l) / sizeof((*__l).x)); ++i) \
    { *(__l.x + i) -= *(__r.x + i); } \
  } \
}

#define D_sub_vector_to(__l, \
                        __r, \
                        __v) \
{ \
  if (!D_check_vectors3(__l, __r, __v)) \
  { D_raise_error(DERR_VECS3); } \
  else \
  { \
    /* Iterates through the struct's members  */ \
    for (i32 i = 0; i < (sizeof(*__l) / sizeof((*__l).x)); ++i) \
    { *(__v.x + i) = *(__l.x + i) - (*(__r.x + i)); } \
  } \
}

#define D_mult_vector(__l, \
                      __r) \
{ \
  if (!D_check_vectors2(__l, __r)) \
  { D_raise_error(DERR_VECS2); } \
  else \
  { \
    /* Iterates through the struct's members  */ \
    for (i32 i = 0; i < (sizeof(*__l) / sizeof((*__l).x)); ++i) \
    { (*(__l.x + i))*= (*(__r.x + i)); } \
  } \
}

#define D_mult_vector_to(__l, \
                         __r, \
                         __v) \
{ \
  if (!D_check_vectors3(__l, __r, __v)) \
  { D_raise_error(DERR_VECS3); } \
  else \
  { \
    /* Iterates through the struct's members  */ \
    for (i32 i = 0; i < (sizeof(*__l) / sizeof((*__l).x)); ++i) \
    { *(__v.x + i) = (*(__l.x + i)) * (*(__r.x + i)); } \
  } \
}

#define D_div_vector(__l, \
                     __r) \
{ \
  if (!D_check_vectors2(__l, __r)) \
  { D_raise_error(DERR_VECS2); } \
  else \
  { \
    /* Iterates through the struct's members  */ \
    for (i32 i = 0; i < (sizeof(*__l) / sizeof((*__l).x)); ++i) \
    { \
      /* Checks if divisor is 0 before dividing. */ \
      if (*(__r.x + i) != 0) \
      { *(__l.x + i) /= (*(__r.x + i)); } \
    } \
  } \
}

#define D_div_vector_to(__l, \
                        __r, \
                        __v) \
{ \
  if (!D_check_vectors3(__l, __r, __v)) \
  { D_raise_error(DERR_VECS3); } \
  else \
  { \
    /* Iterates through the struct's members  */ \
    for (i32 i = 0; i < (sizeof(*__l) / sizeof((*__l).x)); ++i) \
    { \
      /* Checks if divisor is 0 before dividing. */ \
      if (*(__r.x + i) != 0) \
      { *(__v.x + i) = (*(__l.x + i)) / (*(__r.x + i)); } \
    } \
  } \
}

#define D_mag_vector_to(__l, \
                        __r) \
{ *__r = sqrt(((*__l).x) * ((*__l).x) + ((*__l).y * (*__l).y)); }

#define D_norm_vector(__v) \
{ D_div_vector(__v, __v); }

#define D_rotation_vector(__v) -atan2((f64)-((*__v).y), (*__v).x)

#define D_rotation_vector_to(__l, \
                             __r) \
{ *__r = D_rotation_vector(__l); }

#define D_rotate_vector(__type, \
                        __v, \
                        __d) \
{ \
  /* Stores a temporary .x value */ \
  __type *temp_x = (__type *)malloc(sizeof(__type)); \
  *temp_x = (*__v).x; \
  \
  (*__v).x = ((cos(__d)) * (*temp_x)) - ((sin(__d)) * ((*__v).y)); \
  (*__v).y = ((sin(__d)) * (*temp_x)) + ((cos(__d)) * ((*__v).y)); \
  \
  free(temp_x); \
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_VECTOR_H__ */
