cmake_minimum_required(VERSION 3.1.0...3.27.0)

project(Hivegame)

set ( CMAKE_CXX_STANDARD          11 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS        OFF )

file(GLOB SOURCES "*.cpp")

add_executable(Hivegame ${SOURCES})