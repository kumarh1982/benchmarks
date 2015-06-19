#!/usr/bin/make -f
CC=g++
SOURCE_DIR=.
SOURCES =  false_sharing.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = false_sharing

CFLAGS= -I. -std=c++11 -c -g

all: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
		$(CC) $(OBJECTS) -pthread  -o $@ 

.cpp.o: *.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	@echo Cleaning
	-rm -f $(OBJECTS) $(EXECUTABLE)
	@echo Cleaning done
	
.PHONY: all clean