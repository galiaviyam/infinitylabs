target: prerequisites

.PHONY: do Foo Bla

do: 
	gcc -g -c -fPIC so1.c
	gcc -g -c -fPIC dynso_test.c 
	gcc -g -shared so1.o -o so1.so
	gcc  dynso_test.c -o dynso_test

prerequisites: do

Foo:
	./dynso_test ./so1.so Foo
	
Bla:
	./dynso_test ./so1.so Bla	
