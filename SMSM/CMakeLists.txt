cmake_minimum_required(VERSION 3.0)
project(SMRT)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wunused -std=c++1y")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")

file(GLOB_RECURSE SRC src/*.cpp)

add_library(smsm SHARED ${SRC})

add_definitions(-DSMSM_EXPORT)

# Local includes
target_include_directories(smsm PUBLIC include)
target_include_directories(smsm PRIVATE .)

install(TARGETS smsm LIBRARY DESTINATION lib)
install(DIRECTORY include/SMSM DESTINATION include)