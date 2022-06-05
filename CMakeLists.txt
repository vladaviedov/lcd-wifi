cmake_minimum_required(VERSION 3.0)

project(lcd-wifi VERSION 0.1)
set(CMAKE_C_FLAGS "-Wall -Wextra" CACHE STRING "" FORCE)
set(CMAKE_BUILD_TYPE Debug)
file(GLOB SOURCES src/*.c)
add_executable(lcd-wifi ${SOURCES})

target_link_libraries(lcd-wifi i2c)
