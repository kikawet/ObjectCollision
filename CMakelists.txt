cmake_minimum_required(VERSION 3.10)

# set the project name
project(ObjectCollision)

set(CMAKE_CXX_COMPILER g++)
# set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Generate config.h
configure_file(include/config.h.in config.h)

list(APPEND CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules")

# Find SFML shared libraries
find_package(SFML # 2.4
    COMPONENTS 
        system window graphics REQUIRED
    )

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        )

add_executable(ObjectCollision "${all_SRCS}")

# Set include directory search paths
target_include_directories(ObjectCollision 
  PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
  )

# Link executable to required SFML modules
target_link_libraries(ObjectCollision sfml-system sfml-graphics sfml-window)