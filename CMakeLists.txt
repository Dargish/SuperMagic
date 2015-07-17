cmake_minimum_required(VERSION 3.0)
project(SMOG)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wunused -std=c++1y")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")

add_subdirectory(smog)
add_subdirectory(smsm)
add_subdirectory(app)
