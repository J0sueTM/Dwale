# Dwale

#### _An open source, efficiency focused game framework_

# Clone

Remember that dwale has vendors and submodules.

```sh
$ git clone --recursive https://github.com/J0sueTM/Dwale.git
```

If you don't want the development branch:

```sh
$ git clone --recursive --branch stable https://github.com/J0sueTM/Dwale.git
```

If you want to add dwale as a submodule:

```sh
$ git submodule add https://github.com/J0sueTM/Dwale.git vendor/Dwale
$ git submodule update --init --recursive
```

## Install

There is already a premake5 workspace ready to use.

* Linux
Any gnu make works perfect.
  ```sh
  $ premake5 *
  
  # * = The generated file type. Whether gmake or gmake2
  #   | gmake
  #   | gmake2

  $ make # for compiling
  ```
  
* Unix
I haven't tested on unix yet. However, I don't think it differs that much from linux. Please open a PR or an issue if there's something wrong.
  ```sh
  $ premake5 *
  
  # * = The generated file type. For mac os I recommend:
  #   | gmake
  #   | gmake2
  #   | xcode4

  $ make # for compiling
  ```
  
* Windows
I recommend using Visual Studio. I haven't tested with any other IDE or compiler.
  ```batch
  $ premake5 *
 
  :: * = The version of your Visual Studio.
  ::   | vs2005
  ::   | vs2006
  ::   | vs2007
  ::   | vs2008
  ::   | vs2009
  ::   | vs2010
  ::   | vs2011
  ::   | vs2012
  ::   | vs2013
  ::   | vs2014
  ::   | vs2015
  ::   | vs2016
  ::   | vs2017
  ::   | vs2018
  ::   | vs2019
  ```

## Dependencies

All Dwale dependencies are already into the vendor folder.

| Vendor | Website | Source Code |
| ------ | ------- | ----------- |
| GLFW | https://glfw.org | https://github.com/glfw/glfw |
| GLAD | https://glad.dav1d.de/ | https://github.com/dav1dde/glad-web |
| CGLM | https://cglm.readthedocs.io/en/latest/ | https://github.com/recp/cglm |
| STB | https://nothings.org/stb/stb_h.html | https://github.com/nothings/stb |

Check out [Premake's documentation if you're stuck](https://premake.github.io/docs/).

A project by Josué Teodoro Moreira

