file(GLOB_RECURSE SRC src/*.cpp)

add_library(smog SHARED ${SRC})

add_definitions(-DSMOG_EXPORT)

# Local includes
target_include_directories(smog PUBLIC include)
target_include_directories(smog PRIVATE .)

target_link_libraries(smog GLEW GL jsoncpp)

install(TARGETS smog LIBRARY DESTINATION lib)
install(DIRECTORY include/SMOG DESTINATION include)