cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_COMPILER "C:/MinGW/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")

project(Dwale VERSION 1.0 LANGUAGES C)
set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON CACHE BOOL "" FORCE)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/include
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

add_library(Dwale SHARED ${SRC})
if (WIN32)
  target_link_libraries(Dwale mingw32 glad glfw cglm opengl32 OpenGL::GL)
else ()
  target_link_libraries(Dwale glad glfw cglm OpenGL::GL)
endif (WIN32)
