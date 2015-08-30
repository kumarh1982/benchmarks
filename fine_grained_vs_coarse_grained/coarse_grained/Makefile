#!/usr/bin/make -f
CC=g++
SOURCE_DIR=.
SOURCES =  coarse_grained_queue.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = coarse_grained_queue

CFLAGS= -I. -std=c++11 -c 

all: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
		$(CC) $(OBJECTS) -o2 -pthread  -o $@ 

.cpp.o: *.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	@echo Cleaning
	-rm -f $(OBJECTS) $(EXECUTABLE)
	@echo Cleaning done
	
.PHONY: all clean