set(SYSTEM_SOURCE_FILES 
	audio_system.h
	audio_system.cpp
	collision_system.h
	collision_system.cpp
	health_system.h
	health_system.cpp
	input_system.h
	input_system.cpp
	life_time_system.h
	life_time_system.cpp
	physics_system.h
	physics_system.cpp
	render_system.h
	render_system.cpp
)

add_library(SYSTEMS ${SYSTEM_SOURCE_FILES})
target_link_libraries(SYSTEMS COMPONENTS)
