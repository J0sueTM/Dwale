# file test/CMakeFiles.txt
# author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
# date July 20, 2021
#
# Copyright (C) Josué Teodoro Moreira
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

cmake_minimum_required(VERSION 3.20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

project(DwaleTest VERSION 1.0 LANGUAGES C)

add_executable(DebugTest ${CMAKE_CURRENT_SOURCE_DIR}/src/t_debug.c)
target_link_libraries(DebugTest Dwale)

add_executable(VectorTest ${CMAKE_CURRENT_SOURCE_DIR}/src/t_vector.c)
target_link_libraries(VectorTest Dwale)

add_executable(MatrixTest ${CMAKE_CURRENT_SOURCE_DIR}/src/t_matrix/t_matrix.c)
target_link_libraries(MatrixTest Dwale OpenGL::GL)

add_executable(WindowTest ${CMAKE_CURRENT_SOURCE_DIR}/src/t_window.c)
target_link_libraries(WindowTest Dwale OpenGL::GL)

add_executable(GLObjectTest ${CMAKE_CURRENT_SOURCE_DIR}/src/t_gl_object.c)
target_link_libraries(GLObjectTest Dwale OpenGL::GL)

add_executable(TextureTest ${CMAKE_CURRENT_SOURCE_DIR}/src/t_texture/t_texture.c)
target_link_libraries(TextureTest Dwale OpenGL::GL)

add_executable(SurfaceTest ${CMAKE_CURRENT_SOURCE_DIR}/src/t_surface/t_surface.c)
target_link_libraries(SurfaceTest Dwale OpenGL::GL)

add_executable(CameraTest ${CMAKE_CURRENT_SOURCE_DIR}/src/t_camera/t_camera.c)
target_link_libraries(CameraTest Dwale OpenGL::GL)

add_executable(AudioTest ${CMAKE_CURRENT_SOURCE_DIR}/src/t_audio/t_audio.c)
target_link_libraries(AudioTest Dwale)
