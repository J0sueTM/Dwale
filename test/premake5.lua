--[[
-- \file test/premake5.lua
-- \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
-- \date April 21, 2021
--
-- Copyright (C) Josué Teodoro Moreira
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

project "DebugTest"
  kind "ConsoleApp"
  language "C"

  targetdir("../bin/test/%{prj.name}")
  objdir("../bin/obj/test/%{prj.name}")

  files
  { "./src/t_debug.c" }

  includedirs
  { "../inc" }

  links
  {
    "GLAD",
    "GLFW",
    "Dwale"
  }

  systemversion "latest"
  staticruntime "On"

  filter "system:linux"
    linkoptions
    {
      "-lpthread",
      "-lGL",
      "-lXi",
      "-lX11",
      "-lXrandr",
      "-lm",
      "-ldl"
    }
  filter "system:windows"
    defines
    { "_CRT_SECURE_NO_WARNINGS" }
  filter "configurations:Debug"
    runtime "Debug"
    symbols "On"
  filter "configurations:Release"
    runtime "Release"
    optimize "On"
  filter ""
