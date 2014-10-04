set(SYSTEM_SOURCE_FILES 
	input_system.h
	input_system.cpp
	physics_system.h
	physics_system.cpp
	render_system.h
	render_system.cpp
)

add_library(SYSTEMS ${SYSTEM_SOURCE_FILES})
target_link_libraries(SYSTEMS ECS)
