
LIB_NAME = axMidi

## Platform name.
UNAME := $(shell uname)

## 32 vs 64 bits.
ARCH := $(shell getconf LONG_BIT)

## x86 vs arm.
PROCESSOR_TYPE := $(shell uname -m)

INCLUDE_SRC = -Iinclude

## LINUX
ifeq ($(UNAME), Linux)

## RASPBERRY PI
ifeq ($(PROCESSOR_TYPE), armv7l)
CC = g++-4.9
CC_FLAGS = -std=c++14 -Wall -pedantic
else
## x86 ARCHITECTURE
CC = clang++
CC_FLAGS = -std=c++11 -Wall -pedantic
endif

INCLUDE_SRC += /usr/include/

STATIC_LIB_NAME = lib$(LIB_NAME).a
DYN_LIB_NAME = lib$(LIB_NAME).so
endif

## MAC
ifeq ($(UNAME), Darwin)
CC = clang++
CC_FLAGS = -std=c++11 -Wall

INCLUDE_SRC += -I/usr/local/include/

STATIC_LIB_NAME = lib$(LIB_NAME).a
DYN_LIB_NAME = lib$(LIB_NAME).dylib
endif

INCLUDE_SRC = -Iinclude -I/usr/local/include/ -I../Utils/include/

OBJDIR = build
SRC_DIR = source
INCLUDE_DIR = include/

CPP_FILES := $(wildcard source/*.cpp)
OBJ_FILES := $(addprefix build/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS :=

all: createDir $(OBJ_FILES)
	ar rcs lib/$(STATIC_LIB_NAME) $(OBJ_FILES)

createDir:
	@mkdir -p build lib

build/%.o: source/%.cpp
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) -c -o $@ $<

clean:
	rm -f $(OBJDIR)/*.o
	rm -f lib/$(STATIC_LIB_NAME)



