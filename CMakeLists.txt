cmake_minimum_required(VERSION 3.27)
project(MagicSquare C)

set(CMAKE_C_STANDARD 11)

add_executable(MagicSquare main.c
        magic_square.h)
