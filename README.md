# Image processor

Program written on C++ with OpenGL's GLSL shaders to transform images by applying kernel convolutions.

![Application GUI view](./res/screenshot1.png)

## What is this?

Application created to process texture with various kernels:
* Edge detecting kernels ([Prewitt](https://en.wikipedia.org/wiki/Prewitt_operator), 
[Sobel](https://en.wikipedia.org/wiki/Prewitt_operator), 
Scharr)
* Smoothing kernels (Average)
* Denoising kernels (Median)

Created with:
* [SDL2](https://www.libsdl.org/) and [SDL2_image](https://www.libsdl.org/projects/SDL_image/)
* [ImGui](https://github.com/ocornut/imgui/)
* [OpenGL](https://wikipedia.org/wiki/OpenGL)

## How to build

Requirements:
* OpenGL >= 4.2, or otherwise:
    * change **_kOpenGlVersion_** and **_kGlslVersion_** in [application_config.h](./app/application_config.h))
    * change **_API_** version in [glad2_loader/CMakeLists.txt](./3rd_party/glad2_loader/CMakeLists.txt)
    * fix **_.frag_** shaders in [shaders/](./res/shaders)
* C++ compiler supporting C++20 standard
* CMake >= 3.15
    * otherwise, try change **_VERSION_** in [CMakeLists.txt](./CMakeLists.txt)
* Installed [SDL2](https://www.libsdl.org/download-2.0.php) & [SDL2_image](https://www.libsdl.org/projects/SDL_image/) libraries
    
Clone project with submodules (choose one of the repositories):
```shell script
git clone https://github.com/ValeryKameko/image-processor --recurse-submodules
git clone https://gitlab.com/ValeryKameko/image-processor --recurse-submodules
```
Build CMake project:
```shell script
cd    ./image-processor
mkdir ./cmake-build-release
cd    ./cmake-build-release
cmake .. -DCMAKE_BUILD_TYPE=Release
```

To run application:
```shell script
cd ./bin

# for WINDOWS
./image-processor.exe

# for Linux
./image-processor
```

Tested on:
* Windows (GNU GCC 9.0 MinGW, CMake 3.15, OpenGL 4.6)
