set(CORE_SOURCE_FILES 
	component.h
	entity.h
	entity.cpp
	game_objects.h
	game_objects.cpp
	level.h
	level.cpp
	engine.h
	engine.cpp
	system.h	
)

add_library(CORE ${CORE_SOURCE_FILES})
