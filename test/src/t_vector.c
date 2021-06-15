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

void
_text();

int
main(int    argc,
     char **argv)
{
  vec2 test_vector1 = { 20.43f, 0.6f };
  vec2 test_vector2 = { 10.0f, 2.4f };
  vec2 test_vector3;
  vec4 test_vector4 = { 43.1f, 33.9f, 32.44f, 102.48f };
  vec4 test_vector5 = { 3.4f, 968.8f, 865.2f, 0.4f };
  vec4 test_vector6;

  /* add */
  glm_vec2_add(test_vector1, test_vector2, test_vector3);
  printf("Expects 30.43 : 3.00\nGot     %.2f : %.2f\n", test_vector3[0], test_vector3[1]);

  test_vector1[0] = 0.4f;
  test_vector1[1] = 0.94f;
  glm_vec2_add(test_vector2, test_vector1, test_vector1);
  printf("\nExpects 10.40 : 3.34\nGot     %.2f : %.2f\n", test_vector1[0], test_vector1[1]);

  glm_vec4_add(test_vector4, test_vector5, test_vector6);
  printf("\nExpects 46.50 : 1002.70 : 897.64 : 102.88\nGot     %.2f : %.2f : %.2f : %.2f\n", test_vector6[0],
                                                                                             test_vector6[1],
                                                                                             test_vector6[2],
                                                                                             test_vector6[3]);

  /* sub */
  glm_vec2_sub(test_vector3, test_vector1, test_vector3);
  printf("\nExpects 20.03 : -0.34\nGot     %.2f : %.2f\n", test_vector3[0], test_vector3[1]);

  glm_vec2_sub(test_vector4, test_vector1, test_vector3);
  printf("\nExpects 32.70 : 30.56\nGot     %.2f : %.2f\n", test_vector3[0], test_vector3[1]);

  /* mult */
  test_vector1[0] = 2.0f;
  test_vector2[0] = 9.4f;
  test_vector1[1] = 3.0f;
  test_vector2[1] = 4.2f;
  glm_vec2_mul(test_vector1, test_vector2, test_vector1);
  printf("\nExpects 18.80 : 12.60\nGot     %.2f : %.2f\n", test_vector1[0], test_vector1[1]);

  test_vector1[0] = 2.0f;
  test_vector2[1] = 9.4f;
  glm_vec2_mul(test_vector1, test_vector2, test_vector3);
  printf("\nExpects 18.80 : 52.92\nGot     %.2f : %.2f\n", test_vector3[0], test_vector3[1]);

  /* div */
  test_vector1[0] = 8.2f;
  test_vector2[0] = 4.1f;
  test_vector1[1] = 9.3f;
  test_vector2[1] = 3.1f;
  glm_vec2_div(test_vector1, test_vector2, test_vector1);
  printf("\nExpects 2.00 : 3.00\nGot     %.2f : %.2f\n\n", test_vector1[0], test_vector1[1]);

  return 0;
}
