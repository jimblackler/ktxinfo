cmake_minimum_required(VERSION 3.13)

add_subdirectory(ktx)

set(CMAKE_CXX_STANDARD 14)

add_executable(ktxinfo main.c info.c info.h glnames.c glnames.h)

target_link_libraries(ktxinfo ktx)

target_include_directories(ktxinfo PRIVATE ktx/include)
