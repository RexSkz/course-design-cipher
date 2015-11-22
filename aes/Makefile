OBJECTS = main.o \
		  aes.o \
		  sha256.o

SRCS = main.cpp \
	   sha256.c \
	   aes.cpp

aes: $(OBJECTS)
	g++ -o aes $(OBJECTS)

main.o: main.cpp
	g++ -c main.cpp -o main.o

aes.o: aes.cpp
	g++ -c aes.cpp -o aes.o

sha256.o: sha256.c
	g++ -c sha256.c -o sha256.o

clean:
	rm -rf *.o *.exe *.ans