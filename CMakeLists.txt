cmake_minimum_required(VERSION 3.10)

project(azoya)

add_executable(azoya main.cpp)

install(TARGETS azoya RUNTIME DESTINATION bin)
