set(COMPONENT_SOURCE_FILES 
	collision.h
	collision.cpp
	damage.h
	damage.cpp
	health.h
	health.cpp
	life_time.h
	life_time.cpp
        physics_body.h
        physics_body.cpp
	shape.h
	shape.cpp
	texture.h
	texture.cpp
	velocity.h
	velocity.cpp	
)

add_library(COMPONENTS ${COMPONENT_SOURCE_FILES})
target_link_libraries(COMPONENTS CORE)
