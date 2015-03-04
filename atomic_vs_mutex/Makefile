#!/usr/bin/make -f
CC=g++
SOURCE_DIR=.
SOURCES =  atomic_vs_mutex.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = atomic_vs_mutex

CFLAGS= -I. -pthread -std=c++11 -c
LFLAGS= -pthread

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