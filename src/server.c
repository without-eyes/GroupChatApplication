#include "../include/socketutil.h"

struct AcceptedSocket {
    int acceptedSocketFD;
    struct sockaddr_in address;
    int error;
    bool acceptedSuccessfully;
};

struct AcceptedSocket acceptedSockets[10];
int acceptedSocketsCount = 0;

struct AcceptedSocket* acceptIncomingConnection(int serverSocketFD);
void* receiveAndPrintIncomingData(void *td);
void startAcceptingIncomingConnections(int serverSocketFD);
void receiveAndPrintIncomingDataOnSeparateThread(struct AcceptedSocket *pSocket);
void sendReceiveMessageToTheOtherClients(char* buffer, int socketFD);

int main() {
    int serverSocketFD = createTCPIpv4Socket();
    struct sockaddr_in* serverAddress = createIPv4Address("", 2000);

    int result = bind(serverSocketFD, (struct sockaddr*)serverAddress, sizeof(*serverAddress));
    if (result == 0) {
        printf("Socket was bound successfully!\n");
    } else {
        printf("Error!\n");
    }

    listen(serverSocketFD, 10);

    startAcceptingIncomingConnections(serverSocketFD);

    // shutdown(serverSocketFD, SHUT_RDWR);
}

struct AcceptedSocket* acceptIncomingConnection(int serverSocketFD) {
    struct sockaddr_in clientAddress;
    unsigned int clientAddressSize = sizeof(clientAddress);
    int clientSocketFD = accept(serverSocketFD, (struct sockaddr*) &clientAddress, &clientAddressSize);

    struct AcceptedSocket* acceptedSocket = (struct AcceptedSocket*)malloc(sizeof(struct AcceptedSocket));
    acceptedSocket->address = clientAddress;
    acceptedSocket->acceptedSocketFD = clientSocketFD;
    acceptedSocket->acceptedSuccessfully = clientSocketFD > 0;
    if (!acceptedSocket->acceptedSuccessfully) {
        acceptedSocket->error = clientSocketFD;
    }

    return acceptedSocket;
}

void* receiveAndPrintIncomingData(void *td) {
    int* socketFD = (int*)td;

    char buffer[4096];
    while (true) {
        ssize_t amountReceived = recv(*socketFD, &buffer, sizeof(buffer), 0);

        if (amountReceived > 0) {
            buffer[amountReceived] = 0;
            printf("%s\n", buffer);

            sendReceiveMessageToTheOtherClients(buffer, *socketFD);
        } else {
            break;
        }
    }

    close(*socketFD);
    return NULL;
}

void sendReceiveMessageToTheOtherClients(char* buffer, int socketFD) {
    for (int i = 0; i <acceptedSocketsCount; i++) {
        if (acceptedSockets[i].acceptedSocketFD != socketFD) {
            send(acceptedSockets[i].acceptedSocketFD, buffer, strlen(buffer), 0);
        }
    }
}

void receiveAndPrintIncomingDataOnSeparateThread(struct AcceptedSocket *pSocket) {
    pthread_t id;
    pthread_create(&id, NULL, receiveAndPrintIncomingData, &pSocket->acceptedSocketFD);
}

void startAcceptingIncomingConnections(int serverSocketFD) {
    while (true) {
        struct AcceptedSocket* clientSocket = acceptIncomingConnection(serverSocketFD);
        acceptedSockets[acceptedSocketsCount++] = *clientSocket;
        receiveAndPrintIncomingDataOnSeparateThread(clientSocket);
    }
}

