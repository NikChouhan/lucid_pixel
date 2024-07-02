cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(home_DIR ${CMAKE_CURRENT_SOURCE_DIR}/)

project(lucid_pixel)

#include(C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake) 

find_package(OpenGL REQUIRED)
#find_package(glfw3 CONFIG REQUIRED)
#find_package(glad REQUIRED)

file(GLOB_RECURSE SRC_FILES "src/*.cpp" "includes/*.hpp" "includes/*.h")
add_executable(lucid_pixel main.cpp ${SRC_FILES})

set_target_properties(lucid_pixel PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${home_DIR})

file(GLOB_RECURSE IMGUI_FILES "imgui/*.cpp" "imgui/*.h" "imgui/*.hpp" "imgui/*.c" "imgui/*.inl")
add_library(imgui STATIC ${IMGUI_FILES})

#target_include_directories(lucid_pixel PUBLIC ${glad_DIR})
target_include_directories(lucid_pixel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)
target_include_directories(lucid_pixel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui)

target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)

find_library(GLFW_LIB NAMES glfw3 glfw PATHS ${CMAKE_CURRENT_SOURCE_DIR}/includes/glfw/lib NO_DEFAULT_PATH)

target_link_libraries(imgui PRIVATE ${GLFW_LIB})
target_link_libraries(lucid_pixel OpenGL::GL imgui ${GLFW_LIB})

# For GLAD, include its header directory and add its source file to the project
target_include_directories(lucid_pixel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/glad/include)
# If glad.c is not in your SRC_FILES, add it directly here
target_sources(lucid_pixel PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes/glad/src/glad.c)