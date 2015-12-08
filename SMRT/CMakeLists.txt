cmake_minimum_required(VERSION 3.0)
project(SMRT)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -Wunused -std=c++1y")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")

include_directories($ENV{BOB_WORLD_SLOT_ilmbase}/include/OpenEXR)

file(GLOB_RECURSE SRC src/*.cpp)

add_library(smrt SHARED ${SRC})

# Local includes
target_include_directories(smrt PUBLIC include)
target_include_directories(smrt PRIVATE .)

install(TARGETS smrt LIBRARY DESTINATION lib)
install(DIRECTORY include/SMRT DESTINATION include)