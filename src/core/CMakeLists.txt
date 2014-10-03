set(CORE_SOURCE_FILES 
	level.h
	level.cpp
	engine.h
	engine.cpp
)

add_library(CORE ${CORE_SOURCE_FILES})
target_link_libraries(CORE ECS)
