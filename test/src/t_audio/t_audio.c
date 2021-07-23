/**
 * \file test/src/t_audio.c
 * \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
 * \date July 20, 2021
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
main()
{
  D_init();

  struct D_window *window = D_create_window("AudioTest", 800, 600, -1, true, true);

  struct D_audio_stream *test_audio_stream = D_create_audio_stream("test/src/t_audio/res/working.ogg", 0.0f, 5.0f, 1.0f, true);
  struct D_audio_stream *another_test_audio_stream = D_create_audio_stream("test/src/t_audio/res/working.ogg", 0.0f, 5.0f, 1.0f, false);
    
  D_play_audio_stream(test_audio_stream);

  bool up_state = false, down_state = false;
  while (D_is_window_open(window))
  {
    D_clear_window(0.2f, 0.2f, 0.2f, 1.0f);

    if (glfwGetKey(window->handle, GLFW_KEY_D) == GLFW_PRESS)
      D_set_audio_stream_offset(test_audio_stream, 3.0f);
    else if (glfwGetKey(window->handle, GLFW_KEY_A) == GLFW_PRESS)
      D_pause_audio_stream(test_audio_stream);
    else if(glfwGetKey(window->handle, GLFW_KEY_S) == GLFW_PRESS)
      D_play_audio_stream(test_audio_stream);
    else if (glfwGetKey(window->handle, GLFW_KEY_T) == GLFW_PRESS)
      D_play_audio_stream(another_test_audio_stream);
    else if (glfwGetKey(window->handle, GLFW_KEY_UP) == GLFW_PRESS)
    {
      if (!up_state)
      {
        D_set_audio_stream_gain(test_audio_stream, test_audio_stream->gain + 0.1f);

        up_state = true;
      }
    }
    else if (glfwGetKey(window->handle, GLFW_KEY_UP) == GLFW_RELEASE)
      up_state = false;
    else if (glfwGetKey(window->handle, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
      if (!down_state)
      {
        D_set_audio_stream_gain(test_audio_stream, test_audio_stream->gain - 0.1f);

        down_state = true;
      }
    }
    else if (glfwGetKey(window->handle, GLFW_KEY_DOWN) == GLFW_RELEASE)
      down_state = false;

    D_swap_window_buffers();
    D_poll_window_events();
  }

  D_end_audio_stream(another_test_audio_stream);
  D_end_audio_stream(test_audio_stream);
  
  D_end();
  
  return 0;
}
