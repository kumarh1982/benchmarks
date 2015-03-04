#!/usr/bin/make -f
CC=g++
SOURCE_DIR=.
SOURCES =  virtual_methods.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = virtual_methods

CFLAGS= -I. -std=c++11 -c -pg
LFLAGS= -pg

benchmark1: CFLAGS += -fno-inline
benchmark1: all

benchmark2: CFLAGS += -O3 -fno-inline
benchmark2: all

benchmark3: CFLAGS +=  -O3
benchmark3: all

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