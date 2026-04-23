cmake_minimum_required(VERSION 3.16)
project(SpringCPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include(FetchContent)
FetchContent_Declare(
    yaml-cpp
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
    GIT_TAG        yaml-cpp-0.7.0
)
set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(yaml-cpp)

target_compile_options(yaml-cpp PRIVATE -include cstdint)

add_library(spring_cpp STATIC
    src/core/container.cpp
    src/core/injectable.cpp
    src/dependency-resolver/di_graph.cpp
    src/config/yaml_config.cpp
)

target_include_directories(spring_cpp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(spring_cpp PUBLIC yaml-cpp::yaml-cpp)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE spring_cpp)

add_custom_target(run
    COMMAND main
    DEPENDS main
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_SOURCE_DIR}/bin)