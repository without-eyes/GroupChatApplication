CC = gcc

SERVERSRC = src/server.c \
			src/socketutil.c

CLIENTSRC = src/client.c \
			src/socketutil.c

server: server_compile server_run clean
client:	client_compile client_run clean

.PHONY: server client
.SILENT: server client

server_compile:
	$(CC) $(SERVERSRC) -o server

server_run:
	./server

client_compile:
	$(CC) $(CLIENTSRC) -o client

client_run:
	./client

clean:
	rm -f ./server ./client
