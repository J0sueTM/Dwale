--[[
-- file vendor/cglm/premake5.lua
-- author Josué Teodoro Moreira <jteodomo@gmail.com>
-- date May 20, 2021
--
-- Copyright (C) 2021 Josué Teodoro Moreira 
--
-- This program is free software; you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation; either version 2 of the License, or
-- (at your option) any later version.
--
-- This program is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
--]]

project "CGLM"
  kind "StaticLib"
  language "C"

  targetdir("bin/" .. outputdir .. "-%{prj.name}")
  objdir("bin/obj/" .. outputdir .. "-%{prj.name}")

  files
  {
    "src/euler.c",
    "src/affine.c",
    "src/io.c",
    "src/quat.c",
    "src/cam.c",
    "src/vec2.c",
    "src/vec3.c",
    "src/vec4.c",
    "src/mat2.c",
    "src/mat3.c",
    "src/mat4.c",
    "src/plane.c",
    "src/frustum.c",
    "src/box.c",
    "src/project.c",
    "src/sphere.c",
    "src/ease.c",
    "src/curve.c",
    "src/bezier.c",
    "src/ray.c",
    "src/affine2d.c"
  }

  filter "configurations:Debug"
    runtime "Debug"
    symbols "On"
    defines
    { "__D_DEBUG__" }
  filter "configurations:Release"
    runtime "Release"
    optimize "On"
    defines
    { "__D_RELEASE__" }
  filter ""
