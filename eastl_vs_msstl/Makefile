#!/usr/bin/make
CC=g++
SOURCES =  main.cpp ./src/allocator.cpp ./src/assert.cpp ./src/fixed_pool.cpp ./src/hashtable.cpp ./src/red_black_tree.cpp ./src/string.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = ea_stl_test

CFLAGS= -I. -I./include -std=c++11 -fPIC -DPIC -c -O3 -Ofast -funroll-loops -w
LFLAGS=-fPIC -DPIC -lstdc++

all: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
		$(CC) $(LFLAGS) $(OBJECTS) -o $@ 

.cpp.o: *.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	@echo Cleaning
	-rm -f $(OBJECTS) $(EXECUTABLE)
	@echo Cleaning done
	
.PHONY: all clean