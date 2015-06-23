CC=g++
OPTIMIZATION=-O3

CFLAGS=-g -Wall -Werror -std=c++11 $(OPTIMIZATION)

EXECUTIBLE=binc
SOURCES=interface/cmdbinding.cpp core/parser.cpp core/lexer.cpp core/error.cpp core/lookup.cpp
BUILD_DIR = build


# replace all appearance of .cpp with .o
OBJECTS=${SOURCES:%.cpp=${BUILD_DIR}/%.o}


all: $(EXECUTIBLE)
	cp binc.exe bin/

# $@ is automatic variable for target name
$(EXECUTIBLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo Compiling $<
	$(CC) $(CFLAGS) -c -o $@ $<

${SOURCES}:
	@echo Creating $@
	@mkdir -p $(dir $@)

clean:
	rm -rf *o $(EXECUTIBLE)

test: $(EXECUTIBLE)
	valgrind -q --track-origins=yes ./$(EXECUTIBLE)
