/**
 * \file test/src/t_debug.c
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date April 21, 2021
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

int
main(int    argc,
     char **argv)
{
  D_raise_log("Log is working");
  D_raise_warning("This is a warning!");
  D_raise_error("This is probably an error!!!");

  /* NULL error, should raise errno */
  FILE *nonexistent_file = fopen("/usr/lib/random_name.c");
  D_assert(nonexistent_file, NULL);

  return 0;
}
