all:	
	g++ -w -c src/matrix_generic.cpp src/data.cpp src/regress.cpp
	ar rcs lib/libcmlt0.2.a matrix_generic.o data.o regress.o
	rm matrix_generic.o data.o regress.o
	cp lib/libcmlt0.2.a /usr/lib/
