cmake_minimum_required(VERSION 3.28)
project(GroupChatApplication C)

set(CMAKE_C_STANDARD 11)

add_executable(GroupChatApplication
    include/socketutil.h
    src/client.c
    src/server.c
    src/socketutil.c)