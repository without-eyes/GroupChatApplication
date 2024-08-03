#include "../include/socketutil.h"

int main() {
    int serverSocketFD = createTCPIpv4Socket();
    struct sockaddr_in* serverAddress = createIPv4Address("", 2000);

    int result = bind(serverSocketFD, serverAddress, sizeof(*serverAddress));
    if (result == 0) {
        puts("Socket was bound successfully!\n");
    }

    int listenResult = listen(serverSocketFD, 10);

    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof(clientAddress);
    int clientSocketFD = accept(serverSocketFD, &clientAddress, &clientAddressSize);

    char buffer[4096];
    while (1) {
        ssize_t amountReceived = recv(clientSocketFD, &buffer, sizeof(buffer), 0);

        if (amountReceived > 0) {
            buffer[amountReceived] = 0;
            printf("Response: %s\n", buffer);
        } else {
            break;
        }
    }

    close(clientSocketFD);
    shutdown(serverSocketFD, SHUT_RDWR);
}
