file(GLOB_RECURSE SRC *.cpp)

add_executable(smrt_app ${SRC})

target_link_libraries(smrt_app smrt)

# External libs and includes
target_link_libraries(
	smrt_app
		IlmImf
		pthread
	)

set_target_properties(smrt_app PROPERTIES OUTPUT_NAME smrt_app)

install(TARGETS smrt_app RUNTIME DESTINATION bin)
