cmake_minimum_required(VERSION 3.23)
project(Criptografia C)

set(CMAKE_C_STANDARD 99)

add_executable(Criptografia main.c)

add_executable(feistel feistel.h feistel.c )
add_executable(teste01 teste01.c)