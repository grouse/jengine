set(ECS_SOURCE_FILES 
	component_manager.hpp
	components.hpp
	entity_manager.h
	entity_manager.cpp
)

add_library(ECS ${ECS_SOURCE_FILES})
