
LIB_NAME = axRender

UNAME := $(shell uname)

## MAC
ifeq ($(UNAME), Darwin)
CC = clang++
CC_FLAGS = -std=c++11 -Wall
STATIC_LIB_NAME = lib$(LIB_NAME).a
DYN_LIB_NAME = lib$(LIB_NAME).dylib
INCLUDE_SRC = -Iinclude/ -I/usr/local/include/ -I/usr/local/include/freetype2/ -I../Utils/include/
INCLUDE_LINKER = -L../Utils/lib/ -L/usr/local/lib/
LINKER_FLAG = -lpng -lUtils -lfreetype -framework OpenGL

else ifeq ($(UNAME), FreeBSD)
CC = clang++
CC_FLAGS = -std=c++11 -Wall -fPIC -DaxCoreX11 -DGL_GLEXT_PROTOTYPES=1
STATIC_LIB_NAME = lib$(LIB_NAME).a
DYN_LIB_NAME = lib$(LIB_NAME).so
INCLUDE_SRC = -Iinclude/ -I/usr/local/include/ -I/usr/local/include/freetype2/ -I../Utils/include/
INCLUDE_LINKER = -L../axUtils/lib/ -L/usr/local/lib/
LINKER_FLAG = -lpng -laxUtils -lfreetype -framework OpenGL

## LINUX
else ifeq ($(UNAME), Linux)

## RASPBERRY PI
#ifeq ($(PROCESSOR_TYPE), armv7l)

INCLUDE_SRC = -Iinclude/ -I/usr/include/freetype2 -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/ -I/usr/local/include/ -I/usr/local/include/freetype2/ -I../axUtils/include/
INCLUDE_LINKER = -L../axUtils/lib/ -L/usr/lib/ -L/opt/vc/lib/
LINKER_FLAG = -lpng -laxUtils -lfreetype -lEGL -lGLESv1_CM

CC = g++-4.9
CC_FLAGS = -DANDROID -DGL_GLEXT_PROTOTYPES=1 -std=c++14 -Wall -pedantic -Wno-variadic-macros
#else

## x86 ARCHITECTUREi
#INCLUDE_SRC = -Iinclude/ -I/usr/include/freetype2/ -I/usr/include/ -I/usr/local/include/ -I../axUtils/include/
#
#INCLUDE_LINKER = -L../axUtils/lib/ -L/usr/lib/
#LINKER_FLAG = -lpng -laxUtils -lfreetype
#
#CC = clang++
#CC_FLAGS = -std=c++11 -Wall -pedantic -fPIC -DaxCoreX11 -DGL_GLEXT_PROTOTYPES=1
#
#endif

STATIC_LIB_NAME = lib$(LIB_NAME).a
DYN_LIB_NAME = lib$(LIB_NAME).so
endif

OBJDIR = build
SRC_DIR = source
INCLUDE_DIR = include/

CPP_FILES := $(wildcard source/*.cpp)
OBJ_FILES := $(addprefix build/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS :=

all: create_dir  $(OBJ_FILES)
	ar rcs lib/$(STATIC_LIB_NAME) $(OBJ_FILES)

build/%.o: source/%.cpp
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) -c -o $@ $<

create_dir:
	@mkdir -p build lib

clean:
	rm -f $(OBJDIR)/*.o
	rm -f lib/$(STATIC_LIB_NAME)



