target: prerequisites

.PHONY: do Foo Bla

do: 
	g++ -c -fPIC shared_object.cpp
	g++ -shared -o libshared_object.so shared_object.o
	g++ -c -fPIC sec_part.cpp
	g++  sec_part.cpp -o sec_part

prerequisites: do

Foo:
	./sec_part ./libshared_object.so Foo
	
clean:
	rm *.o libshared_object.so sec_part
