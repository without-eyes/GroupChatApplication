#ifndef GROUPCHATAPPLICATION_SOCKETUTIL_H
#define GROUPCHATAPPLICATION_SOCKETUTIL_H

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>

int createTCPIpv4Socket();

struct sockaddr_in* createIPv4Address(char *ip, int port);

#endif //GROUPCHATAPPLICATION_SOCKETUTIL_H
