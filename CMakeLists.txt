cmake_minimum_required(VERSION 3.13)

add_subdirectory(ktx)
add_subdirectory(simplejson)


set(CMAKE_CXX_STANDARD 14)

add_executable(ktxinfo main.c info.cpp glnames.c string_utils.cpp update.cpp)

target_link_libraries(ktxinfo ktx simplejson)

target_include_directories(ktxinfo PRIVATE ktx ktx/include simplejson variadictable)
