CC=g++
OPTIMIZATION=-O3

CFLAGS=-Wall -Werror -std=c++11
DEBUG_FLAGS=-g -DDEBUG_BUILD

EXECUTIBLE=binc
SOURCES=interface/cmdbinding.cpp core/parser.cpp core/lexer.cpp core/error.cpp core/lookup.cpp
BUILD_DIR = build


# replace all appearance of .cpp with .o
OBJECTS=${SOURCES:%.cpp=${BUILD_DIR}/%.o}


all: CFLAGS += $(OPTIMIZATION)
all: $(EXECUTIBLE)
	cp binc.exe bin/

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(EXECUTIBLE)

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
	rm -rf build/* $(EXECUTIBLE)

test: $(EXECUTIBLE)
	valgrind -q --track-origins=yes ./$(EXECUTIBLE)
