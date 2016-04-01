LIB_NAME = axAudio

## Platform name.
UNAME := $(shell uname)

## MAC
ifeq ($(UNAME), Darwin)
CC = clang++
CC_FLAGS = -std=c++11 -Wall
STATIC_LIB_NAME = lib$(LIB_NAME).a
DYN_LIB_NAME = lib$(LIB_NAME).dylib
endif


## LINUX
ifeq ($(UNAME), Linux)
CC = clang++
CC_FLAGS = -std=c++11 -Wall
STATIC_LIB_NAME = lib$(LIB_NAME).a
DYN_LIB_NAME = lib$(LIB_NAME).so

# else ## RASPBERRY PI
# CC = g++-4.9
# CC_FLAGS = -std=c++14 -Wall -pedantic
endif

INCLUDE_SRC = -Iinclude -I/usr/local/include/ -I../Utils/include/

OBJDIR = build
SRC_DIR = source
INCLUDE_DIR = include/

CPP_FILES := $(wildcard source/*.cpp)
OBJ_FILES := $(addprefix build/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS :=

all: $(OBJ_FILES)
	ar rcs lib/$(STATIC_LIB_NAME) $(OBJ_FILES)
	# $(CC) $(CC_FLAGS) -dynamiclib $(OBJ_FILES) -o lib/$(DYN_LIB_NAME)

build/%.o: source/%.cpp
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) -c -o $@ $<

clean:
	rm -f $(OBJDIR)/*.o
	rm -f lib/$(STATIC_LIB_NAME)



