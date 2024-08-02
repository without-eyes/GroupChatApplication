#include "../include/socketutil.h"

int main() {
    int socketFD = createTCPIpv4Socket();
    struct sockaddr_in* address = createIPv4Address("127.0.0.1", 2000);

    int result = connect(socketFD, address, sizeof(*address));
    if (result == 0) {
        puts("Connection was successful!\n");
    }

    char* message = "GET \\ HTTP/1.1\r\nHost:google.com\r\n\r\n";
    send(socketFD, message, strlen(message), 0);

    char buffer[4096];
    recv(socketFD, &buffer, sizeof(buffer), 0);

    printf("Response: %s\n", buffer);

    close(socketFD);
}
