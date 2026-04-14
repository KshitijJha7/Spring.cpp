cmake_minimum_required(VERSION 3.16)
project(SpringCPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Header-only library
add_library(spring_cpp INTERFACE)

target_include_directories(spring_cpp INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Executable
add_executable(main main.cpp)

target_link_libraries(main PRIVATE spring_cpp)

add_custom_target(run
    COMMAND main
    DEPENDS main
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)