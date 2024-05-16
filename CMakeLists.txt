cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lucid_pixel) 

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")
add_executable(lucid_pixel main.cpp ${SRC_FILES} src/glad.c)
file(GLOB_RECURSE IMGUI_FILES "imgui/*.cpp")
add_library(imgui STATIC ${IMGUI_FILES})

target_include_directories(lucid_pixel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)
target_include_directories(lucid_pixel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui)

target_link_libraries(lucid_pixel OpenGL::GL glfw imgui dl)
