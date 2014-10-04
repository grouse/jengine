set(CORE_SOURCE_FILES
	globals.h
	globals.cpp	
	level.h
	level.cpp
	engine.h
	engine.cpp
)

add_library(CORE ${CORE_SOURCE_FILES})
target_link_libraries(CORE SYSTEMS)
