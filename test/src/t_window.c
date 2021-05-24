/**
 * \file test/src/t_window.c
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date April 23, 2021
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
  D_init();
  struct D_window *test_window = D_create_window("Dwale", 800, 600, -1, true, false);
  D_set_window_view((vec4){0.2f, 0.2f, 0.8f, 0.8f});

  while (D_is_window_open(test_window))
  {
    if (glfwGetKey(test_window->handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    { goto end_all; }
    
    D_clear_window(0.2f, 0.4f, 0.1f, 1.0f);

    D_swap_window_buffers();
    D_poll_window_events();
  }

end_all:  
  D_end_window(test_window);
  D_end();

  return 0;
}
