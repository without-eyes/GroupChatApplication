CC = gcc
CFLAGS = -s -o

SERVERSRC = src/server.c \
			src/socketutil.c

CLIENTSRC = src/client.c \
			src/socketutil.c

server: server_compile server_run clean
client:	client_compile client_run clean

.PHONY: server client
.SILENT: server client server_compile server_run clean client_compile client_run

server_compile:
	$(CC) $(SERVERSRC) $(CFLAGS) server

server_run:
	./server

client_compile:
	$(CC) $(CLIENTSRC) $(CFLAGS) client

client_run:
	./client

clean:
	rm -f ./server ./client
