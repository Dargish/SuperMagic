file(GLOB_RECURSE SRC *.cpp)

add_executable(smog_app ${SRC})

target_link_libraries(smog_app smog smsm)

# External libs and includes
target_link_libraries(
	smog_app
		sfml-audio
		sfml-graphics
		sfml-network
		sfml-system
		sfml-window
	)

set_target_properties(smog_app PROPERTIES OUTPUT_NAME smog_app)

install(TARGETS smog_app RUNTIME DESTINATION bin)
install(DIRECTORY shaders DESTINATION share)
install(DIRECTORY materials DESTINATION share)
