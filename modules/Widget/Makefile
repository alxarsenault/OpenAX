
LIB_NAME = axWidget

UNAME := $(shell uname)

## MAC
ifeq ($(UNAME), Darwin)
CC = clang++
CC_FLAGS = -std=c++11 -Wall
STATIC_LIB_NAME = lib$(LIB_NAME).a
DYN_LIB_NAME = lib$(LIB_NAME).dylib

INCLUDE_SRC = -Iinclude/ -I../Core/include/ -I../Event/include/ -I../Xml/include/ -I../Render/include/ -I/usr/local/include/ -I/usr/local/include/freetype2/ -I../Utils/include/

else ifeq ($(UNAME), FreeBSD)

STATIC_LIB_NAME = lib$(LIB_NAME).a
DYN_LIB_NAME = lib$(LIB_NAME).so

INCLUDE_SRC = -Iinclude/ -I../axCore/include/ -I../axEvent/include/ -I../axRender/include/ -I/usr/local/include/ -I/usr/local/include/freetype2/ -I../axUtils/include/

INCLUDE_LINKER = -L../axUtils/lib/ -L/usr/lib/
LINKER_FLAG = -lpng -laxUtils -lfreetype -lGL -laxXml

CC = clang++
CC_FLAGS = -DaxCoreX11 -fPIC -std=c++11 -Wall 

## LINUX
else ifeq ($(UNAME), Linux)
	#CC = g++
	#CC_FLAGS = -std=c++0x -Wall
STATIC_LIB_NAME = lib$(LIB_NAME).a
DYN_LIB_NAME = lib$(LIB_NAME).so

INCLUDE_SRC = -Iinclude/ -I../axCore/include/ -I../axEvent/include/ -I../axGL/include/ -I/usr/include/freetype2 -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/ -I/usr/local/include/ -I/usr/local/include/freetype2/ -I../axUtils/include/

INCLUDE_LINKER = -L../axUtils/lib/ -L/usr/lib/ -L/opt/vc/lib/
LINKER_FLAG = -lpng -laxUtils -lfreetype -lEGL -lGLESv1_CM

#CC = clang++
#CC_FLAGS = -DaxCoreX11 -fPIC -std=c++11 -Wall 

## WINDOWS
# else
#
# ## RASPBERRY PI
CC = g++-4.9
CC_FLAGS = -DANDROID -DGL_GLEXT_PROTOTYPES=1 -std=c++14 -Wall -pedantic -Wno-variadic-macros
endif


OBJDIR = build
SRC_DIR = source
INCLUDE_DIR = include/

CPP_FILES := $(wildcard source/*.cpp)
OBJ_FILES := $(addprefix build/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS :=

all: create_dir $(OBJ_FILES)
	ar rcs lib/$(STATIC_LIB_NAME) $(OBJ_FILES)
	# $(CC) $(CC_FLAGS) -dynamiclib $(OBJ_FILES) -o lib/$(DYN_LIB_NAME)

install: $(OBJ_FILES)
	@mkdir -p /usr/local/lib/axLib/
	cp lib/$(DYN_LIB_NAME) /usr/local/lib/axLib/
	@mkdir -p /usr/local/include/axLib/
	cp $(wildcard include/*.h) /usr/local/include/axLib/


build/%.o: source/%.cpp
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) -c -o $@ $<

create_dir:
	@mkdir -p build lib

clean:
	rm -f $(OBJDIR)/*.o
	rm -f lib/$(STATIC_LIB_NAME)


