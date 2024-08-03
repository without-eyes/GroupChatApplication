#include "../include/socketutil.h"

int main() {
    int socketFD = createTCPIpv4Socket();
    struct sockaddr_in* address = createIPv4Address("127.0.0.1", 2000);

    int result = connect(socketFD, address, sizeof(*address));
    if (result == 0) {
        puts("Connection was successful!\n");
    }

    char* line = NULL;
    size_t lineSize = 0;
    printf("Type and we will send(type exit)...\n");

    while (1) {
        ssize_t charCount = getline(&line, &lineSize, stdin);

        if (charCount > 0) {
            if (strcmp(line, "exit\n") == 0) {
                break;
            }

            send(socketFD, line, charCount, 0);
        }
    }

    close(socketFD);
}
