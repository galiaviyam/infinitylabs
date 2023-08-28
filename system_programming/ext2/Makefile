WS = ext2
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
TARGET = a.out
SOURCE = $(WS)_test.c $(WS).c
objects = $(WS).o $(WS)_test.o
HEADER = $(WS).h

all: $(TARGET)
	
$(TARGET): $(SOURCE) $(objects)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

debug: $(CFLAGS) += -DDEBUG
debug: $(TARGET)

release: $(CFLAGS) += -DNDEBUG -O3
release: $(TARGET)

run: $(TARGET)
	@sudo ./$(TARGET)
clean:
	rm *.o $(TARGET)
