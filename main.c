#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main() {
    // creating socket file descriptor
    // AF_INET - address family inet(IPv4)
    // SOCK_STREAM - TCP connection
    int socketFD = socket(AF_INET, SOCK_STREAM, 0);

    char* ip = "142.250.203.206";
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(80); // host to network short
    inet_pton(AF_INET, ip, &address.sin_addr.s_addr); // inet presentation to network

    int result = connect(socketFD, (struct sockaddr*) &address, sizeof(address));

    if (result == 0) {
        puts("Connection was successful!\n");
    }

    char* message = "GET \\ HTTP/1.1\r\nHOST:www.google.com\r\n\r\n";
    send(socketFD, message, strlen(message), 0);

    char buffer[1024];
    recv(socketFD, buffer, 1024, 0);

    printf("Response: %s\n", buffer);

    close(socketFD);
    return 0;
}
