/**
 * \file inc/core/debug.h
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date April 20, 2021
 *
 * \brief Provides utilities for debugging at runtime
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

#ifndef __D_DEBUG_H__
#define __D_DEBUG_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "core/core.h"

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

#define USE_ERRNO NULL

void
D_raise_log(char *__log_buffer);

void
D_raise_warning(char *__warning_buffer);

void
D_raise_error_alt(char *__error_buffer,
                  char *__error_file,
                  i32   __error_line);

#define D_raise_error(__error_buffer) \
  D_raise_error_alt((__error_buffer) \
                      ? __error_buffer \
                      : strerror(errno), \
                    __FILE__, \
                    __LINE__)

#define D_assert(__statement, \
                 __error_buffer) \
  if (!__statement) \
    D_raise_error(__error_buffer)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_DEBUG_H__ */
