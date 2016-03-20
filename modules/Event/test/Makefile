TEST_NAME = test

## Platform name.
UNAME := $(shell uname)

## 32 vs 64 bits.
ARCH := $(shell getconf LONG_BIT)

## x86 vs arm.
PROCESSOR_TYPE := $(shell uname -m)

INCLUDE_SRC = -I../include/
LINKER_FLAGS = 

## LINUX
ifeq ($(UNAME), Linux)

## RASPBERRY PI
ifeq ($(PROCESSOR_TYPE), armv7l)
CC = g++-4.9
CC_FLAGS = -std=c++14 -Wall -pedantic
else
## x86 ARCHITECTURE
CC = clang++
CC_FLAGS = -std=c++11 -Wall
endif

LINKER_FLAGS += ../lib/libaxEvent.a -lpthread
endif

## MAC
ifeq ($(UNAME), Darwin)
CC = clang++
CC_FLAGS = -std=c++11 -Wall

LINKER_FLAGS += ../lib/libaxEvent.a -lpthread
endif

all:
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) test.cpp  $(LINKER_FLAGS) -o $(TEST_NAME)

test2: test2.cpp
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) test2.cpp  $(LINKER_FLAGS) -o test2