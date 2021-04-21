--[[
-- \file premake5.lua
-- \author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
-- \date April 20, 2021
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

workspace "Dwale"
  architecture "x86_64"

  configurations
  {
    "Debug",
    "Release"
  }

  outputdir = "%{cfg.buildcfg}/%{cfg.architecture}-%{cfg.system}"

  includedirs
  {
    "./inc",
    "./vendor/glfw/include",
    "./vendor/glad/include"
  }

  group "libs"
    include "./vendor/glfw"
    include "./vendor/glad"
  group ""

  include "./inc"

  group "unittest"
    include "./test"
  group ""
