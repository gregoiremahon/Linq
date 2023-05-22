#ifndef NETWORK_H
#define NETWORK_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int startServer(int port);
void acceptConnections(Game* game);
void sendPassword(Game* game, char* password);
void receiveWord(Game* game);
void closeSockets(Game* game);

#endif // NETWORK_H
