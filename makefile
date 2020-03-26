
CFLAGS = -L . -Wl,-rpath=.
#CFLAGS = -L
CC = g++
.PHONY: clean

all: client.o server.o errno.so rsa.so
	$(CC) -o client client.o $(CFLAGS) rsa.so $(CFLAGS) errno.so
	$(CC) -o server server.o $(CFLAGS) rsa.so $(CFLAGS) errno.so
	rm client.o server.o 

client.o: client.c socket.h
	$(CC) -c client.c

server.o: server.c socket.h
	$(CC) -c server.c

install:
	$(CC) -shared -fPIC -o errno.so error_functions.c
	$(CC) -shared -fPIC -o rsa.so rsa.c
#	$(CC) -fpic -shared -o errno.so error_functions.c

uninstall:
	rm -rf errno.so rsa.so 

clean:
	rm client server myKey.txt
