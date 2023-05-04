cmake_minimum_required(VERSION 3.21)
project(hw7)
add_executable(hw7 src/main.cpp)
target_include_directories(hw7 PRIVATE includes)
target_link_libraries(hw7 PRIVATE rjsjai)
target_link_directories(hw7 PRIVATE lib)

if(MSVC)
    target_compile_options(hw7 PRIVATE "/MT")
endif()

set_target_properties(
    hw7
    PROPERTIES CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)