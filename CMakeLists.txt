cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(glad_DIR "/usr/include/glad")

set(home_DIR ${CMAKE_CURRENT_SOURCE_DIR}/)

project(lucid_pixel)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(assimp REQUIRED)
#find_package(glad REQUIRED)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")
add_executable(lucid_pixel main.cpp ${SRC_FILES} src/glad.c includes/mesh_loader.cpp includes/Shader.cpp includes/load_texture.cpp)

set_target_properties(lucid_pixel PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${home_DIR})

file(GLOB_RECURSE IMGUI_FILES "imgui/*.cpp" "imgui/*.h" "imgui/*.hpp" "imgui/*.c" "imgui/*.inl")
add_library(imgui STATIC ${IMGUI_FILES})

target_include_directories(lucid_pixel PUBLIC ${glad_DIR})
target_include_directories(lucid_pixel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)
target_include_directories(lucid_pixel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui)


target_link_libraries(lucid_pixel OpenGL::GL glfw imgui dl assimp)
