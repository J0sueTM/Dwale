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

  D_assert(0, "Assertion outputing an error!");

  FILE *nonexistent_file = fopen("nonexistent_file.png", "rb");
  D_assert(nonexistent_file, USE_ERRNO);
  D_assert(nonexistent_file, "You tried to open a file that does not exist :(");

  return 0;
}
