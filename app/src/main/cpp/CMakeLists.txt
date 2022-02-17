cmake_minimum_required(VERSION 3.10.2)
project("coroutine")

#ENABLE_LANGUAGE(ASM)

add_library(
        coroutine
        SHARED
        native-lib.cpp
        OSCoroutine.cpp
        OSThread.cpp
        CoroutineDespatcher.cpp)

find_library(
        log-lib
        log)

target_link_libraries(
        coroutine
        ${log-lib})