
LIB_NAME = axOS
UNAME := $(shell uname)

## MAC
ifeq ($(UNAME), Darwin)
CC = clang++
CC_FLAGS = -std=c++11 -Wall
STATIC_LIB_NAME = lib$(LIB_NAME).a
DYN_LIB_NAME = lib$(LIB_NAME).dylib
endif

ifeq ($(UNAME), FreeBSD)
CC = clang++
CC_FLAGS = -DaxCoreX11 -fPIC -std=c++11 -Wall -pedantic

STATIC_LIB_NAME = lib$(LIB_NAME).a
DYN_LIB_NAME = lib$(LIB_NAME).so
endif

## LINUX
ifeq ($(UNAME), Linux)
CC = clang++
CC_FLAGS = -DaxCoreX11 -fPIC -std=c++11 -Wall -pedantic

STATIC_LIB_NAME = lib$(LIB_NAME).a
DYN_LIB_NAME = lib$(LIB_NAME).so

## RASPBERRY PI
CC = g++-4.9
CC_FLAGS = -DaxCoreAndroid -fPIC -std=c++11 -Wall -pedantic  
endif

INCLUDE_SRC = -Iinclude/ -I../Utils/include/ -I../Event/include/

OBJDIR = build
SRC_DIR = source
INCLUDE_DIR = include/

CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(addprefix build/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS :=

all: create_dir $(OBJ_FILES)
	ar rcs lib/$(STATIC_LIB_NAME) $(OBJ_FILES)

build/%.o: source/%.cpp
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) -c -o $@ $<

create_dir:
	@mkdir -p $(OBJDIR) lib

clean:
	rm -f $(OBJDIR)/*.o
	rm -f lib/$(STATIC_LIB_NAME)



