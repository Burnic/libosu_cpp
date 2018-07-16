cmake_minimum_required(VERSION 3.10)
project(libosu VERSION 1.0 DESCRIPTION "Osu Library for packets, buffers etc." LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(INC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(
  osu SHARED
    ${SRC}/buffer.cpp
    ${SRC}/packet.cpp
    ${SRC}/packetlist.cpp
    ${SRC}/packets.cpp
)

target_include_directories(osu PRIVATE include)