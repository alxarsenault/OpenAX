
LIB_NAME = axEvent

## Platform name.
UNAME := $(shell uname)

## 32 vs 64 bits.
ARCH := $(shell getconf LONG_BIT)

## x86 vs arm.
PROCESSOR_TYPE := $(shell uname -m)

INCLUDE_SRC = -Iinclude/

## LINUX
ifeq ($(UNAME), Linux)

## RASPBERRY PI
ifeq ($(PROCESSOR_TYPE), armv7l)
CC = g++-4.9
CC_FLAGS = -std=c++14 -Wall -pedantic
else
## x86 ARCHITECTURE
CC = clang++
CC_FLAGS = -std=c++11 -Wall -pedantic -fPIC
endif

STATIC_LIB_NAME = lib$(LIB_NAME).a
DYN_LIB_NAME = lib$(LIB_NAME).so
endif

## MAC
ifeq ($(UNAME), Darwin)
CC = clang++
CC_FLAGS = -std=c++11 -Wall

STATIC_LIB_NAME = lib$(LIB_NAME).a
DYN_LIB_NAME = lib$(LIB_NAME).dylib
endif

ifeq ($(UNAME), FreeBSD)
CC = clang++
CC_FLAGS = -std=c++11 -Wall -fPIC

STATIC_LIB_NAME = lib$(LIB_NAME).a
DYN_LIB_NAME = lib$(LIB_NAME).so
endif

OBJDIR = build
SRC_DIR = source
INCLUDE_DIR = include/

CPP_FILES := $(wildcard source/*.cpp)
OBJ_FILES := $(addprefix build/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS :=

all: create_dir $(OBJ_FILES)
	ar rcs lib/$(STATIC_LIB_NAME) $(OBJ_FILES)

build/%.o: source/%.cpp
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) -c -o $@ $<

create_dir:
	@mkdir -p build lib

clean:
	rm -f $(OBJDIR)/*.o
	rm -f lib/$(STATIC_LIB_NAME)



