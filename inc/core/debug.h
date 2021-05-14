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
#define __D_INCLUDE_NONE__
#include "dwale.h"

#define USE_ERRNO NULL

/**
 * \brief Prints a formatted log message
 *
 * \param __log_buffer Specifies a NULL terminated C string
 *                     that will be prompted.
 */
void
D_raise_log(char *__log_buffer);

/**
 * \brief Prints a formatted warning message
 *
 * \param __warning_buffer Specifies a NULL terminated C string
 *                         that will be prompted.
 */  
void
D_raise_warning(char *__warning_buffer);

/**
 * \brief Prints a formatted error message
 *
 * \param __error_buffer Specifies a NULL terminated C string
 *                       that will be prompted.
 * \param __error_file   Specifies the file name where the error occurred.
 * \param __error_line   Specifies the line where the error occurred.
 */
void
D_raise_error_alt(char *__error_buffer,
                  char *__error_file,
                  i32   __error_line);

/**
 * \brief Prints a formatted error message using D_raise_error_alt,
 *        parsing either the error buffer or errno
 *
 * \param __error_buffer Specifies a NULL terminated C string
 *                       that will be prompted.
 */  
#define D_raise_error(__error_buffer) \
  D_raise_error_alt((__error_buffer) \
                      ? __error_buffer \
                      : strerror(errno), \
                    __FILE__, \
                    __LINE__)

/**
 * \brief Raises an error if __statement is false.
 *
 * \param __statement    Specifies the statement to be checked
 *                       whether false or true.
 * \param __error_buffer Specifies a NULL terminated C string
 *                       that will be prompted.
 */  
#define D_assert(__statement, \
                 __error_buffer) \
  if (!__statement) \
  { D_raise_error(__error_buffer); }

/**
 * \brief Raises an error an closes dwale if __statement is false.
 *
 * \param __statement    Specifies the statement to be checked
 *                       whether false or true.
 * \param __error_buffer Specifies a NULL terminated C string
 *                       that will be prompted.
 */
#define D_assert_fatal(__statement, \
                       __error_buffer) \
  if (!__statement) \
  { \
    D_raise_error(__error_buffer); \
    \
    D_end(); \
  }

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __D_DEBUG_H__ */
