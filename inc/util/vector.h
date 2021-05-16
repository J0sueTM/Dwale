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

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_VECTOR_H__ */
