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

#ifndef __D_ERRCODE_H__
#define __D_ERRCODE_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
  
/* colours do not work on windows terminal */
#ifdef _WIN32
#define C_NORMAL ""
#define C_GREEN  ""
#define C_YELLOW ""
#define C_RED    ""
#else
#define C_NORMAL "\e[0m"
#define C_GREEN  "\e[1;92m"
#define C_YELLOW "\e[1;93m"
#define C_RED    "\e[1;91m"
#endif /* _WIN32 */  

/*
 * This error code list should be upgraded throughout development time.
 * If an error is known by errno, just pass a NULL errcode on D_raise_error
 */

/* Dwale specific */
#define DERR_DNOINIT \
  "Dwale was not initialized. Try using D_init() and D_end()"

#define DERR_NOINIT(x) \
  "Could not initialize " x

#define DERR_NOCREATE(x) \
  "Could not create " x

/* Syntax specific */
#define DERR_NOPARAM(x, \
                     y) \
  "Invalid parameter " \
  x \
  ", " \
  y

/* Vendor specific */
#define DERR_OPENGL "Opengl error"

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_ERRCODE_H__ */
