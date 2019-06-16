cmake_minimum_required(VERSION 3.13)

add_subdirectory(ktx)

set(CMAKE_CXX_STANDARD 14)

add_executable(ktxinfo main.c info.cpp glnames.c)

target_link_libraries(ktxinfo ktx)

target_include_directories(ktxinfo PRIVATE ktx ktx/include variadictable)
