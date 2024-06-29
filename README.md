# A simple OpenGL based renderer

As mentioned, a simple renderer written using OpenGL specification, intended to be a summer project. Expect nothing fancy. Not blazing fast, even though I believe in performant code is always good code, and I will try to optimize it as much as possible, I don't trust much in my capabilities xD

### Compiling and Running

#### Linux

Remove all files and folders except run_build.sh, main.cpp files, and includes, imgui and src folders and comment out "include(C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake) " in CMakeLists.txt and follow the steps below:

```
chmod +x run_build.sh
./run_build.sh
```
#### Windows

Add glfw through choco, and build and generate config using CMake-GUI, the easy way
