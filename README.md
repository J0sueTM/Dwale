# Dwale

#### An open source, efficiency focused game engine/framework

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

# Compile

Dwale uses cmake, so unless you get to compile and link Dwale and it's vendors right, I recommend that you use it as well.

```sh
$ mkdir bin
$ cd bin
```

## Create build files

```sh
$ # Debug
$ cmake -S .. -B . -D DWALE_DEBUG=ON
$  
$ # Release
$ cmake -S .. -B .
```

By default, Dwale will build and link statically. If you don't want so:

```sh
$ # Debug
$ cmake -S .. -B . -D DWALE_DEBUG=ON -D BUILD_SHARED_LIBS=ON
$
$ # Release
$ cmake -S .. -B . -D BUILD_SHARED_LIBS=ON
```

## Build

```sh
$ # Debug
$ cmake --build . --target Dwale --config Debug
$  
$ # Release
$ cmake --build . --target Dwale --config Release
```

## Dependencies

All Dwale dependencies are already into the vendor folder, except for OpenGL, which you should have installed on your machine.

| Vendor | Website | Source Code |
| ------ | ------- | ----------- |
| GLFW | https://glfw.org | https://github.com/glfw/glfw |
| GLAD | https://glad.dav1d.de/ | https://github.com/dav1dde/glad-web |
| CGLM | https://cglm.readthedocs.io/en/latest/ | https://github.com/recp/cglm |
| STB | https://nothings.org/stb/stb_h.html | https://github.com/nothings/stb |
| OPENAL SOFT | https://openal-soft.org/ | https://github.com/kcat/openal-soft |

# What I learnt

- OpenGL (Graphics Programming)
- OpenAL (Audio Programming)
- Cmake
- Premake (I used premake before cmake, check the old versions of this repository)

A project by Josué Teodoro Moreira
