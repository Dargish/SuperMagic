file(GLOB_RECURSE SRC src/*.cpp)

add_library(smsm SHARED ${SRC})

add_definitions(-DSMSM_EXPORT)

# Local includes
target_include_directories(smsm PUBLIC include)
target_include_directories(smsm PRIVATE .)

install(TARGETS smsm LIBRARY DESTINATION lib)
install(DIRECTORY include/SMSM DESTINATION include)