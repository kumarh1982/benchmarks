#!/usr/bin/make -f
CC=g++
SOURCE_DIR=.
SOURCES =  locked_ring_buffer_spsc.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = locked_ring_buffer_spsc

CFLAGS= -I. -std=c++11 -c -O2 

all: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
		$(CC) $(OBJECTS) -pthread -o $@ 

.cpp.o: *.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	@echo Cleaning
	-rm -f $(OBJECTS) $(EXECUTABLE)
	@echo Cleaning done
	
.PHONY: all clean