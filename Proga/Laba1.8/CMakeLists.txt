cmake_minimum_required(VERSION 3.26)
project(Laba1_8 C)

set(CMAKE_C_STANDARD 17)

add_executable(Laba1_8 main.c)

# Link the math library
target_link_libraries(Laba1_8 m)
