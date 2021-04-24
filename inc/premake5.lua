--[[
-- file inc/premake5.lua
-- author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
-- data April 20, 2021
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

project "Dwale"
  kind "StaticLib"
  language "C"

  targetdir("../bin/" .. outputdir .. "-%{prj.name}")
  objdir("../bin/obj/" .. outputdir .. "-%{prj.name}")

  files
  {
    "./**.h",
    "../src/**.c"
  }

  includedirs
  {
    "./",
    "../vendor/glfw/include/",
    "../vendor/glad/include/"    
  }

  systemversion "latest"
  staticruntime "On"

  links 
  {
    "GLFW",
    "GLAD"
  }

  filter "system:linux"
    linkoptions
    {
      "-lpthread",
      "-lGL",
      "-lXi",
      "-lX11",
      "-lXrandr",
      "-ldl"
    }
  filter "configurations:Debug"
    runtime "Debug"
    symbols "On"
  filter "configurations:Release"
    runtime "Release"
    optimize "On"
  filter ""
