/**
 * \file inc/core/errcode.h
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date April 22, 2021
 *
 * \brief Error codes for debugging
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

#ifndef __D_ERRCODE_H__
#define __D_ERRCODE_H__

/**
 * NOTE(all): This error code list should be upgraded throughout
 * development time
 */

#define DERR_NOMEMO "Could not allocate memory"
#define DERR_OUTBOUND "Value out of bound"

#endif /* __D_ERRCODE_H__ */

#ifdef __cplusplus
}
#endif /* __cplusplus */
