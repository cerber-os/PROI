CC=g++
CFLAGS=-O2 -Wall --std=c++11

circularList : circularList.o tester.o main.o realSet.o
	$(CC) $(CFLAGS) -o circularList circularList.o tester.o main.o realSet.o
realSet.o : realSet.cpp
	$(CC) $(CFLAGS) -c realSet.cpp
circularList.o : circularList.cpp circularList.h
	$(CC) $(CFLAGS) -c circularList.cpp
tester.o : tester.cpp
	$(CC) $(CFLAGS) -c tester.cpp
main.o : main.cpp
	$(CC) $(CFLAGS) -c main.cpp

.PHONY : clean
clean :
	rm -f circularList circularList.o tester.o main.o realSet.o
