CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=disemvoweler20150101.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=bin/disemvoweler

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -f $(OBJECTS) 
