CC=g++
CFLAGS=-O2 -Wall --std=c++11

realSet : realSet.o main.o 
	$(CC) $(CFLAGS) -o realSet realSet.o main.o
realSet.o : realSet.cpp realSet.h
	$(CC) $(CFLAGS) -c realSet.cpp
main.o : main.cpp
	$(CC) $(CFLAGS) -c main.cpp

.PHONY : clean
clean :
	rm -f realSet realSet.o main.o
