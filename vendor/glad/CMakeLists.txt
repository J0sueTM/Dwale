cmake_minimum_required(VERSION 3.20)

include(GNUInstallDirs)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(glad STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c)
if (WIN32)
  if (MSVC)
    target_link_libraries(glad opengl32 OpenGL::GL)
  else ()
    target_link_libraries(glad OpenGL::GL)
  endif (MSVC)
else ()
  target_link_librarise(glad OpenGL::GL)  
endif (WIN32)

if (WIN32 AND MSVC)
  set_target_properties(glad PROPERTIES
    OUTPUT_NAME glad
    POSITION_INDEPENDENT_CODE ON)
else ()
  set_target_properties(glad PROPERTIES
    OUTPUT_NAME glad
    POSITION_INDEPENDENT_CODE ON)
endif (WIN32 AND MSVC)

install(TARGETS glad
        EXPORT  glad
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
