/**
 * \file src/core/debug.c
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

#include "core/debug.h"

void
D_raise_log(char *__log_buffer)
{
  if (!__log_buffer)
  { return; }

  printf("%s[ LOG ]:%s %s.\n", C_GREEN,
                               C_NORMAL,
                               __log_buffer);
}

void
D_raise_warning(char *__warning_buffer)
{
  if (!__warning_buffer)
  { return; }

  fprintf(stderr, "%s[ WARNING ]:%s %s.\n", C_YELLOW,
                                            C_NORMAL,
                                            __warning_buffer);
}

void
D_raise_error_alt(char *__error_buffer,
                  char *__error_file,
                  i32   __error_line)
{
  char *temp_error_buffer;
  if (!__error_buffer)
  {
    temp_error_buffer = (char *)malloc(22 * sizeof(char));
    temp_error_buffer = "Something went wrong\0";
  }
  else
  { temp_error_buffer = __error_buffer; }
  
  fprintf(stderr, "%s[ ERROR ]:%s %s:%d %s.\n", C_RED,
                                                C_NORMAL,
                                                __error_file,
                                                __error_line,
                                                __error_buffer);

  if (temp_error_buffer != __error_buffer)
  { free(temp_error_buffer); }
}
