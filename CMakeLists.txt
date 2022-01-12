cmake_minimum_required(VERSION 3.20)
project(opengl_arm)

set(CMAKE_CXX_STANDARD 14)

add_executable(opengl_arm main.cpp matrix.h transform.h scenes.h)
target_link_libraries(opengl_arm -lm -lglut -lGLU -lGL)
