all: hw2

hw2: communication.o client.o main.o
	g++ -o hw2 communication.o client.o main.o -lpthread
communication.o:
	g++ -c communication.cpp
client.o: communication.o
	g++ -c client.cpp
main.o: communication.o client.o
	g++ -c main.cpp
clean:
	rm hw2 *.o


