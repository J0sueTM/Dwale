--[[
-- file test/premake5.lua
-- author Josué Teodoro Moreira <teodoro.josue@protonmail.ch>
-- date April 21, 2021
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

  targetdir("./bin/%{prj.name}")
  objdir("./bin/%{prj.name}/obj/")
  
  files
  {
     "./src/t_debug.c",
     "../inc/",
     "../vendor/glad/include",
     "../vendor/glfw/include"
  }

  includedirs
  {
     "../vendor/glfw/include/",
     "../vendor/glad/include/",
     "../inc/"    
  }

  links
  {
    "Dwale",
    "GLFW",
    "GLAD",    
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

project "VectorTest"
  kind "ConsoleApp"
  language "C"

  targetdir("./bin/%{prj.name}")
  objdir("./bin/%{prj.name}/obj/")
  
  files
  {
     "./src/t_vector.c",
     "../inc/",
     "../vendor/glad/include",
     "../vendor/glfw/include"
  }

  includedirs
  {
     "../vendor/glfw/include/",
     "../vendor/glad/include/",
     "../inc/"    
  }

  links
  {
    "Dwale",
    "GLFW",
    "GLAD",    
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

project "WindowTest"
  kind "ConsoleApp"
  language "C"

  targetdir("./bin/%{prj.name}")
  objdir("./bin/%{prj.name}/obj/")

  files
  { "./src/t_window.c" }

  includedirs
  {
     "../vendor/glfw/include/",
     "../vendor/glad/include/",
     "../inc/"    
  }

  links
  {
    "Dwale",
    "GLFW",
    "GLAD",    
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

project "GLObjectTest"
  kind "ConsoleApp"
  language "C"

  targetdir("./bin/%{prj.name}")
  objdir("./bin/%{prj.name}/obj/")

  files
  { "./src/t_gl_object.c" }

  includedirs
  {
     "../vendor/glfw/include/",
     "../vendor/glad/include/",
     "../inc/"    
  }

  links
  {
    "Dwale",
    "GLFW",
    "GLAD",    
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

project "TextureTest"
  kind "ConsoleApp"
  language "C"

  targetdir("./bin/%{prj.name}")
  objdir("./bin/%{prj.name}/obj/")

  files
  { "./src/t_texture/t_texture.c" }

  includedirs
  {
     "../vendor/glfw/include/",
     "../vendor/glad/include/",
     "../inc/"    
  }

  links
  {
    "Dwale",
    "GLFW",
    "GLAD",    
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

