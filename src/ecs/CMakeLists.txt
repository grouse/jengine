set(ECS_SOURCE_FILES 
	components.hpp
	component_manager.h
	component_manager.cpp
	entity_manager.h
	entity_manager.cpp
)

add_library(ECS ${ECS_SOURCE_FILES})
