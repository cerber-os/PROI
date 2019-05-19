CC=g++
CFLAGS=-O2 -Wall --std=c++11

swimmingPool : place.o client.o worker.o randomGen.o swimmingPool.o main.o
	$(CC) $(CFLAGS) -o swimmingPool place.o client.o worker.o randomGen.o swimmingPool.o main.o

place.o : place.cpp
	$(CC) $(CFLAGS) -c place.cpp

client.o : client.cpp
	$(CC) $(CFLAGS) -c client.cpp
worker.o : worker.cpp
	$(CC) $(CFLAGS) -c worker.cpp
randomGen.o : randomGen.cpp
	$(CC) $(CFLAGS) -c randomGen.cpp
swimmingPool.o : swimmingPool.cpp
	$(CC) $(CFLAGS) -c swimmingPool.cpp
main.o : main.cpp
	$(CC) $(CFLAGS) -c main.cpp

.PHONY : clean
clean :
	rm -f swimmingPool place.o  client.o worker.o randomGen.o swimmingPool.o main.o
