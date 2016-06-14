main: server client

server.o: server.cc
	g++ -c -g server.cc
server: server.o
	g++ server.o -lpthread -o server
client.o: client.cc
	g++ -c -g client.cc
client: client.o
	g++ client.o -lpthread -o client

clean: 
	rm *.o
	rm -f server client
