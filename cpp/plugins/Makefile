TARGET = $(shell basename $(CURDIR))
TARGET_LIB = lib$(TARGET).so
LIB_NAME = $(shell dirname $(PWD))

define newline


endef

DEP_LIST =
RUN_MAKEFILES := $(foreach DEP,$(DEP_LIST),$(MAKE) $(MAKECMDGOALS) -C ../$(DEP) $(newline))
OBJ_DIR = $(LIB_NAME)/obj/$(MAKECMDGOALS)
LIB_DIR = $(LIB_NAME)/libs/$(MAKECMDGOALS)
INCLUDE_DIR = $(LIB_NAME)/include/
LIB_DEBUG = $(LIB_NAME)/libs/debug/
LIB_RELEASE = $(LIB_NAME)/libs/release/
OBJ_DEBUG = $(LIB_NAME)/obj/debug/
OBJ_RELEASE = $(LIB_NAME)/obj/release/

CC = g++
CFLAGS = -std=c++11 -pedantic-errors -Wall -Wextra -I$(INCLUDE_DIR)
LDFLAGS = -L$(LIB_DIR) -Wl,-rpath=$(LIB_DIR)
DEP_FLAGS = $(addprefix -l,$(DEP_LIST))

SOURCES = $(wildcard *.cpp)
HEADER = $(SOURCES:.cpp=.hpp)

.PHONY: all clean debug release

all: 
	$(MAKE) debug -s

debug: CFLAGS += -g
debug: $(TARGET_LIB)
			
release: CFLAGS += -DNDEBUG -O3
release: $(TARGET_LIB)

$(TARGET_LIB): $(SOURCES)
	echo $(SOURCES) $(TARGET_LIB)
	$(CC) $(CFLAGS) -shared -fPIC $^ -o $(LIB_DIR)/$@
	
clean:
	rm -f $(LIB_DEBUG)$(TARGET_LIB) $(LIB_RELEASE)$(TARGET_LIB) \
	$(OBJ_DEBUG)$(OBJS) $(OBJ_RELEASE)/$(OBJS) $(SOURCES:.cpp=.d) 
