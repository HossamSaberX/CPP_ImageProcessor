cmake_minimum_required(VERSION 3.27)
project(assign)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(assign
        main.cpp
        stb_image.h
        stb_image_write.h
        image.h
        image.cpp
        ImageProcessor.h
        ImageProcessor.cpp)
