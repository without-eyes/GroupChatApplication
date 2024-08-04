#include "../include/socketutil.h"

void startListeningAndPrintMessagesOnNewThread(int socketFD);

void* listenAndPrint(void *td);

int main() {
    int socketFD = createTCPIpv4Socket();
    struct sockaddr_in* address = createIPv4Address("127.0.0.1", 2000);

    int result = connect(socketFD, (struct sockaddr*) address, sizeof(*address));
    if (result == 0) {
        printf("Connection was successful!\n");
    }

    char* name = NULL;
    size_t nameSize = 0;
    printf("Please enter your name: ");
    ssize_t nameCount = getline(&name, &nameSize, stdin);
    name[nameCount - 1] = 0;

    char* line = NULL;
    size_t lineSize = 0;
    printf("Type and we will send(type exit)...\n");

    startListeningAndPrintMessagesOnNewThread(socketFD);

    char buffer[1024];

    while (true) {
        ssize_t charCount = getline(&line, &lineSize, stdin);
        line[charCount - 1] = 0;
        sprintf(buffer, "[%s] %s", name, line);

        if (charCount > 0) {
            if (strcmp(line, "exit") == 0) {
                break;
            }

            send(socketFD, buffer, strlen(buffer), 0);
        }
    }

    close(socketFD);
}

void startListeningAndPrintMessagesOnNewThread(int socketFD) {
    pthread_t id;
    pthread_create(&id, NULL, listenAndPrint, &socketFD);
}

void* listenAndPrint(void *td) {
    int* socketFD = (int*)td;

    char buffer[4096];
    while (true) {
        ssize_t amountReceived = recv(*socketFD, &buffer, sizeof(buffer), 0);

        if (amountReceived > 0) {
            buffer[amountReceived] = 0;
            printf("%s\n", buffer);
        } else {
            break;
        }
    }

    close(*socketFD);
    return NULL;
}
