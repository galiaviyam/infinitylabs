TARGET = dynamic_lib

CC = gcc
GCFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

.PHONY : all
all : explicit implicit static

static : static_lib.a main.o
	 $(CC) $(GCFLAGS) main.o -L. static_lib.a -o static_exe

explicit_exe : explicit_main.o lib_$(TARGET).so
	$(CC) $(GCFLAGS) explicit_main.o -ldl -o explicit_exe
	
explicit_main.o :explicit_main.c
	$(CC) $(GCFLAGS) -c explicit_main.c
	
implicit_exe : LD_LIBRARY_PATH main.o
	$(CC) $(GCFLAGS) main.o -L. lib_$(TARGET).so -o implicit_exe

.PHONY : LD_LIBRARY_PATH
LD_LIBRARY_PATH : lib_$(TARGET).so
	 export LD_LIBRARY_PATH=$(PWD):$(PD_LIBRARY_PATH)

lib_$(TARGET).so : dynamic_lib_$(TARGET).o
	$(CC) $(GCFLAGS) dynamic_lib_$(TARGET).o -shared -o lib_$(TARGET).so 

dynamic_lib_$(TARGET).o : $(TARGET).c
	$(CC) $(GCFLAGS) -fPIC -c $(TARGET).c -o dynamic_lib_$(TARGET).o


main.o :main.c
	$(CC) $(GCFLAGS) -c main.c

static_lib_$(TARGET).a : static_lib_$(TARGET).o
	ar rcs static_lib_$(TARGET).a static_lib_$(TARGET).o

static_lib_$(TARGET).o : $(TARGET).c
	$(CC) $(GCFLAGS) -c $(TARGET).c -o static_lib_$(TARGET).o

.PHONY : new
new :
	@ touch $(TARGET).h $(TARGET).c
	@ git add -f $(TARGET).h $(TARGET).c
	@ git commit  -m "initail $(TARGET)"
	@ open $(TARGET).h
	@ open $(TARGET).c

