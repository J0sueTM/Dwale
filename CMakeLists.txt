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

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

project(Dwale VERSION 1.0 LANGUAGES C)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON CACHE BOOL "" FORCE)
set(LIBTYPE "STATIC")

include(GNUInstallDirs)
include(GenerateExportHeader)

if (DWALE_DEBUG)
  if (MSVC)
    add_definitions(-DNDEBUG -D_WINDOWS -D_USRDLL)
    add_compile_options(/Gy /Oi)
  else ()
    set(CMAKE_C_FLAGS "-g")
  endif (MSVC)
  set(DEFAULT_BUILD_TYPE "Debug")
else ()
  set(DEFAULT_BUILD_TYPE "Release")
endif (DWALE_DEBUG)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/include
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/openal_soft/include
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/freealut/include
  ${CMAKE_CURRENT_SOURCE_DIR}/inc
  ${CMAKE_CURRENT_SOURCE_DIR}/src)
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
  ${CMAKE_CURRENT_SOURCE_DIR}/src/audio/stb_vorbis.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/audio/audio.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/dwale.c)

# OpenGL
find_package(OpenGL REQUIRED)

# glad
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad)

# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw)

# cglm
if (MSVC)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm)
else ()
  add_library(cglm STATIC
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

# openal_soft
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/openal_soft)

add_library(Dwale STATIC ${SRC})
if (WIN32)
  if (MSVC)
    target_link_libraries(Dwale glad glfw cglm opengl32 OpenGL::GL OpenAL)
  else ()
    target_link_libraries(Dwale mingw32 glad glfw cglm opengl32 OpenGL::GL OpenAL pthread)
  endif (MSVC)
else ()
  target_link_libraries(Dwale glad glfw cglm OpenGL::GL OpenAL pthread)
endif (WIN32)

if (WIN32 AND MSVC)
  set_target_properties(Dwale PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}
    POSITION_INDEPENDENT_CODE ON
    CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
else ()
  set_target_properties(Dwale PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}
    POSITION_INDEPENDENT_CODE ON)
endif (WIN32 AND MSVC)

GENERATE_EXPORT_HEADER(Dwale
BASE_NAME Dwale
EXPORT_MACRO_NAME dwale_export
EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/inc/dwale_export.h
STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC)

install(TARGETS ${PROJECT_NAME}
        EXPORT  ${PROJECT_NAME}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

if (DWALE_DEBUG)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif (DWALE_DEBUG)
