
LIB_NAME = axCore

ifeq ($(CORE_TYPE), axCoreEOS)
LIB_NAME = axCoreEOS
endif

# CORE_TYPE="axCoreEOS"

## Darwin, Linux, FreeBSD
UNAME := $(shell uname)

## 32 vs 64 bits.                                                               
ARCH := $(shell getconf LONG_BIT)                                                  

## x86 vs arm.
PROCESSOR_TYPE := $(shell uname -m) 

## Apple
ifeq ($(UNAME), Darwin)
CC = clang++
CC_FLAGS = -std=c++11 -Wall
STATIC_LIB_NAME = lib$(LIB_NAME).a
DYN_LIB_NAME = lib$(LIB_NAME).dylib
INCLUDE_SRC = -Iinclude/ -I/usr/local/include/ -I/usr/local/include/freetype2/ -I../Utils/include/ -I../Render/include/ -I../Event/include/ -Icore/Mac/ -Icore/eos/ -I../WindowServer/include/ -I../Xml/include/
INCLUDE_LINKER = -L../axUtils/lib/ -L../Render/lib/ -L../Event/lib/ -L../Xml/lib/ -L/usr/local/lib/
LINKER_FLAG = -lpng -laxUtils -laxGL -laxXml -laxEvent -lfreetype -framework OpenGL -framework Cocoa

CORE_OBJDIR = core/Mac/
CORE_SOURCE = core/Mac/axCocoaInterfaceMac.mm core/Mac/AppDelegate.mm core/Mac/axCoreMac.cpp
CORE_OBJ = build/axCocoaInterfaceMac.o build/AppDelegate.o build/axCoreMac.o

ifeq ($(CORE_TYPE), axCoreEOS)
CORE_OBJDIR = core/eos/
CORE_SOURCE = core/eos/axCoreEOS.cpp core/eos/axProgramLoop.cpp core/eos/axClientWM.cpp 
CORE_OBJ = build/axCoreEOS.o build/axProgramLoop.o build/axClientWM.o
endif

endif

## FreeBSD
ifeq ($(UNAME), FreeBSD)
CC = clang++
CC_FLAGS = -std=c++11 -Wall -pedantic -fPIC -DaxCoreX11 -fpermissive -Wno-comment -Wno-variadic-macros -Wno-reorder

STATIC_LIB_NAME = lib$(LIB_NAME).a
DYN_LIB_NAME = lib$(LIB_NAME).so

INCLUDE_SRC = -Iinclude/ -I/usr/local/include/ -I/usr/local/include/freetype2/ -I../axUtils/include/ -I../axGL/include/ -I../axEvent/include/ -Icore/X11/
INCLUDE_LINKER = -L../axUtils/lib/ -L../axGL/lib/ -L../axEvent/lib/ -L/usr/local/lib/
LINKER_FLAG = -lpng -laxUtils -laxGL -laxEvent -lfreetype -lX11 -lpthread

CORE_OBJDIR = core/X11/                                                                           
CORE_SOURCE = core/X11/axCoreX11.cpp                                                          
CORE_OBJ = build/axCoreX11.o 
endif

## Linux
ifeq ($(UNAME),Linux)
	#CC = g++
	#CC_FLAGS = -std=c++0x -Wall
STATIC_LIB_NAME = lib$(LIB_NAME).a
DYN_LIB_NAME = lib$(LIB_NAME).so

## RASPBERRY PI
#ifeq ($(PROCESSOR_TYPE),armv7l)
CC = g++-4.9
CC_FLAGS = -std=c++14 -Wall -pedantic -DANDROID -fpermissive -Wno-comment -Wno-variadic-macros -Wno-reorder

INCLUDE_SRC = -Iinclude/ -I/usr/include/ -I/usr/include/freetype2/ -I../axUtils/include/ -I../axGL/include/ -I../axEvent/include/ -Icore/Android/ -I/opt/vc/include/ -I/opt/vc/include/interface/vcos/pthreads -I /opt/vc/include/interface/vmcs_host/linux
INCLUDE_LINKER = -L../axUtils/lib/ -L../axGL/lib/ -L../axEvent/lib/ -L/usr/local/lib/ -L/opt/vc/lib/
LINKER_FLAG = -lpng -laxUtils -laxGL -laxEvent -lfreetype -lEGL -lGLESv1_CM -lpthread -lopenmaxil -lbcm_host

CORE_OBJDIR = core/Android/
CORE_SOURCE = core/Android/axCoreAndroid.cpp
CORE_OBJ = build/axCoreAndroid.o
#
#else ifeq ($(PROCESSOR_TYPE),x86_64)
#	CC = clang++
#	CC_FLAGS = -std=c++11 -Wall -pedantic -fPIC -DaxCoreX11 -fpermissive -Wno-comment -Wno-variadic-macros -Wno-reorder
#
#	INCLUDE_SRC = -Iinclude/ -I/usr/include/ -I/usr/include/freetype2/ -I../axUtils/include/ -I../axGL/include/ -I../axEvent/include/ -Icore/X11/
#	INCLUDE_LINKER = -L../axUtils/lib/ -L../axGL/lib/ -L../axEvent/lib/ -L/usr/local/lib/
#	LINKER_FLAG = -lpng -laxUtils -laxGL -laxEvent -lfreetype -lX11 -lpthread
#
#	CORE_OBJDIR = core/X11/                                                                           
#	CORE_SOURCE = core/X11/axCoreX11.cpp                                                          
#	CORE_OBJ = build/axCoreX11.o 
#endif # Processor tyoe.f
endif # Linux.

OBJDIR = build
SRC_DIR = source
INCLUDE_DIR = include/

CPP_FILES := $(wildcard source/*.cpp)
OBJ_FILES := $(addprefix build/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS :=

all: create_dir $(OBJ_FILES) $(CORE_OBJ)
	ar rcs lib/$(STATIC_LIB_NAME) $(OBJ_FILES) $(CORE_OBJ)

build/%.o: source/%.cpp
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) -c -o $@ $<

build/axCocoaInterfaceMac.o:
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) -c -o build/axCocoaInterfaceMac.o core/Mac/axCocoaInterfaceMac.mm

build/AppDelegate.o:
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) -c -o build/AppDelegate.o core/Mac/AppDelegate.mm

build/axCoreMac.o:
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) -c -o build/axCoreMac.o core/Mac/axCoreMac.cpp

#------------------------------------------------------------------------------
build/axCoreEOS.o:
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) -c -o build/axCoreEOS.o core/eos/axCoreEOS.cpp

build/axProgramLoop.o:
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) -c -o build/axProgramLoop.o core/eos/axProgramLoop.cpp

build/axClientWM.o:
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) -c -o build/axClientWM.o core/eos/axClientWM.cpp
#------------------------------------------------------------------------------

build/axCoreAndroid.o: core/Android/axCoreAndroid.cpp core/Android/axCoreAndroid.h
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) -c -o build/axCoreAndroid.o core/Android/axCoreAndroid.cpp

build/axCoreX11.o: core/X11/axCoreX11.cpp core/X11/axCoreX11.h                            
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) -c -o build/axCoreX11.o core/X11/axCoreX11.cpp 

build/NSOpenGLView+axPopupWindowCocoaView.o:
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) -c -o build/NSOpenGLView+axPopupWindowCocoaView.o core/Mac/NSOpenGLView+axPopupWindowCocoaView.mm

create_dir:
	@mkdir -p build lib

install: $(OBJ_FILES)
	@mkdir -p /usr/local/lib/axLib/
	cp $(wildcard lib/*.a) /usr/local/lib/
	@mkdir -p /usr/local/include/axLib/
	cp $(wildcard include/*.h) /usr/local/include/axLib/
	cp $(wildcard core/eos/*.h) /usr/local/include/axLib/

clean:
	@echo $(UNAME)
	@echo $(PROCESSOR_TYPE);
	rm -f $(OBJDIR)/*.o
	rm -f $(CORE_OBJ)
	rm -f lib/$(STATIC_LIB_NAME)



