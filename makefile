rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

CPP_FILES := $(call rwildcard, src/, *.cpp)
OBJ_FILES := obj/stb_image.o $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

GLM_HPP := $(wildcard lib/glm/*.hpp)
GLM_OBJ := $(addprefix obj/,$(notdir $(GLM_HPP:.hpp=.o)))


CC = g++
DEBUG = -g -Wall
CFLAGS = -c -std=c++11 -MMD $(DEBUG)
LFLAGS = -lGL -lSDL2 $(DEBUG)
INC = -Ilib/stb -Ilib -Isrc

jengine: $(OBJ_FILES)
	$(CC) $(LFLAGS) -o $@ $^

$(GLM_OBJ): $(GLM_HPP)
	$(CC) $(CFLAGS) -o $@ $<

obj/stb_image.o: lib/stb/stb_image.c lib/stb/stb_image.h
	$(CC) $(CFLAGS) -o $@ $<

obj/main.o: src/main.cpp
	$(CC) $(CFLAGS) $(INC) -o $@ $<

obj/%.o: src/**/%.cpp
	$(CC) $(CFLAGS) $(INC) -o $@ $<

-include $(OBJ_FILES:.o=.d)
