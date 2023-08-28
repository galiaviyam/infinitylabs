#----------- Variables -----------
NAME = $(shell basename $(PWD))
DIR_NAME = $(shell dirname $(PWD))

TARGET = a.out
SOURCES = $(NAME).c $(NAME)_test.c  
OBJs = $(NAME).o $(NAME)_test.o
HEADER = $(INCLUDE_DIR)$(NAME).h

INCLUDE_DIR := $(DIR_NAME)/include/
LIB_DEBUG := $(DIR_NAME)/libs/debug
LIB_RELEASE := $(DIR_NAME)/libs/release
OBJ_DEBUG := $(DIR_NAME)/obj/debug
OBJ_RELEASE := $(DIR_NAME)/obj/release

#---------- Dependencies ----------
DEPS = dlist
DEP_HEADERS = $(addsuffix .h,$(addprefix $(INCLUDE_DIR)/,$(DEPS)))
DEP_DEBUG_LIBS = $(addsuffix .so,$(addprefix $(LIB_DEBUG)/lib,$(DEPS)))
DEP_RELEASE_LIBS = $(addsuffix .so,$(addprefix $(LIB_RELEASE)/lib,$(DEPS)))

DEP_CREATE_DEBUG = $(addsuffix .debug_dep,$(DEPS))
DEP_CREATE_RELEASE = $(addsuffix .release_dep,$(DEPS))

#------ Compiler definitions -------
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I$(INCLUDE_DIR)
LDFLAGS = -shared
DBGFLAGS = -DDEBUG
RELFLAGS = -DNDEBUG -O3

#-------------- Rules --------------
all: debug release

test: debug $(NAME)_test.c $(LIB_DEBUG)/lib$(NAME).so
	$(CC) $(CFLAGS) -o $(TARGET) -L$(LIB_DEBUG) $(filter-out $<,$^) $(DEP_DEBUG_LIBS)
	
debug: CFLAGS += $(DBGFLAGS)
debug: $(DEP_CREATE_DEBUG) $(LIB_DEBUG)/lib$(NAME).so

release: $(CFLAGS) += $(RELFLAGS)
release: $(DEP_CREATE_RELEASE) $(LIB_RELEASE)/lib$(NAME).so

%.debug_dep:
	@ cd $(DIR_NAME)/$* && $(MAKE) debug

%.release_dep:
	@ cd $(DIR_NAME)/$* && $(MAKE) release
	
$(LIB_DEBUG)/lib%.so: $(OBJ_DEBUG)/%.o
	$(CC) $(LDFLAGS) $< -o $@ -L$(LIB_DEBUG) $(filter-out $<,$^) $(DEP_DEBUG_LIBS)

$(LIB_RELEASE)/lib%.so: $(OBJ_RELEASE)/%.o
	$(CC) $(LDFLAGS) $< -o $@ -L$(LIB_RELEASE) $(filter-out $<,$^) $(DEP_RELEASE_LIBS)

$(OBJ_DEBUG)/%.o: %.c $(INCLUDE_DIR)/%.h $(DEP_HEADERS)
	$(CC) $(CFLAGS) $< -c -o $@ -fPIC

$(OBJ_RELEASE)/%.o: %.c $(INCLUDE_DIR)/%.h $(DEP_HEADERS)
	$(CC) $(CFLAGS) $< -c -o $@ -fPIC

vlg: test
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)

run: test
	./$(TARGET)

$(NAME)_test.o: $(NAME)_test.c
	$(CC) $(CFLAGS) $< -c -fPIC

clean:
	find $(DIR_NAME) \( -name "*$(NAME).so" -o -name "*$(NAME).o" \) -type f -delete
	rm -f $(TARGET)
	
.PHONY: all clean test vlg debug release
