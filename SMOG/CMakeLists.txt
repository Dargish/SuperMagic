cmake_minimum_required(VERSION 3.0)
project(SMOG)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wunused -std=c++1y")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")

file(GLOB_RECURSE SRC src/*.cpp)

add_library(smog SHARED ${SRC})

add_definitions(-DSMOG_EXPORT)

# Local includes
target_include_directories(smog PUBLIC include)
target_include_directories(smog PRIVATE .)

target_link_libraries(smog GLEW GL jsoncpp)

install(TARGETS smog LIBRARY DESTINATION lib)
install(DIRECTORY include/SMOG DESTINATION include)