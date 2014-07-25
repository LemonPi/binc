CC=g++
CFLAGS=-g -Wall -Werror -std=c++11 
EXECUTIBLE=bc
SOURCES=bc.cpp
# replace all appearance of .cpp with .o
OBJECTS=$(SOURCES:.cpp=.o)

all: $(EXECUTIBLE)

# $@ is automatic variable for target name
$(EXECUTIBLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -c 

clean:
	rm -rf *o bc

test: $(EXECUTIBLE)
	valgrind -q --track-origins=yes ./$(EXECUTIBLE)
