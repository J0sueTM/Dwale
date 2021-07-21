# file CMakeFiles.txt
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

project(Dwale VERSION 1.0 LANGUAGES C)
set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON CACHE BOOL "" FORCE)

if (DWALE_DEBUG)
  set(CMAKE_C_FLAGS "-g")
endif (DWALE_DEBUG)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/include
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/portaudio/include
  ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/core/debug.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/video/video.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/video/window.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/video/gl/stb_image.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/video/gl/shader.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/video/gl/texture.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/video/gl/gl_object.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/video/surface.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/video/camera.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/video/renderer.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/audio/audio.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/dwale.c)

# OpenGL
find_package(OpenGL REQUIRED)

# glad
add_library(glad SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/src/glad.c)

# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw)

# cglm
if (MSVC)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm)
else ()
  add_library(cglm SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/src/euler.c
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/src/affine.c
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/src/io.c
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/src/quat.c
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/src/cam.c
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/src/vec2.c
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/src/vec3.c
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/src/vec4.c
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/src/mat2.c
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/src/mat3.c
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/src/mat4.c
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/src/plane.c
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/src/frustum.c
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/src/box.c
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/src/project.c
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/src/sphere.c
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/src/ease.c
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/src/curve.c
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/src/bezier.c
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/src/ray.c
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/src/affine2d.c)
endif (MSVC)

# portaudio
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/portaudio)

add_library(Dwale SHARED ${SRC})
if (WIN32)
  if (MSVC)
    target_link_libraries(Dwale glad glfw cglm portaudio opengl32 OpenGL::GL)
  else ()
    target_link_libraries(Dwale mingw32 glad glfw cglm portaudio opengl32 OpenGL::GL)
  endif (MSVC)
else ()
  target_link_libraries(Dwale glad glfw cglm portaudio OpenGL::GL)
endif (WIN32)

if (DWALE_DEBUG)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif (DWALE_DEBUG)
