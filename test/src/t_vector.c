/**
 * \file test/src/t_vector.c
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date May 18, 2021
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

#include "dwale.h"

int
main(int    argc,
     char **argv)
{
  struct f32vec2 test_vector1 =
  { .x = 20.43f, .y = 0.6f };
  struct f32vec2 test_vector2 =
  { .x = 10.0f, .y = 2.4f };
  struct f32vec2 test_vector3;

  D_add_vector_to(test_vector1, test_vector2, test_vector3);
  printf("Should be 30.43 : 3.00 = %.2f : %.2f\n", test_vector3.x, test_vector3.y);

  test_vector1.x = 0.4f;
  test_vector1.y = 0.94f;
  D_add_vector(test_vector1, test_vector2);
  printf("Should be 10.40 : 3.34 = %.2f : %.2f\n", test_vector1.x, test_vector1.y);

  struct f32vec4 test_vector4 =
  { .x = 43.1f, .y = 33.9f, .z = 32.44f, .w = 102.48f };
  struct f32vec4 test_vector5 =
  { .x = 3.4f, .y = 968.8f, .z = 865.2f, .w = 0.4f };
  struct f32vec4 test_vector6;

  D_add_vector_to(test_vector4, test_vector5, test_vector6);
  printf("Should be 46.50 : 1002.70 : 897.64 : 102.88 = %.2f : %.2f : %.2f : %.2f\n", test_vector6.x,
                                                                                      test_vector6.y,
                                                                                      test_vector6.z,
                                                                                      test_vector6.w);

  return 0;
}
