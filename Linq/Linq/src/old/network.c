#include "network.h"
#include "game.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int startServer(int port) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Binding the socket to the port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    return server_fd;
}

void acceptConnections(Game* game) {
    for (int i = 0; i < game->numPlayers; i++) {
        struct sockaddr_in address;
        int addrlen = sizeof(address);
        int new_socket = accept(game->serverSocket, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        game->players[i].socket = new_socket;
    }
}

void sendPassword(Game* game, char* password) {
    for (int i = 0; i < game->numPlayers; i++) {
        if (game->players[i].role == SPY) {
            send(game->players[i].socket, password, strlen(password), 0);
        }
    }
}

void receiveWord(Game* game) {
    char buffer[256];
    recv(game->players[game->currentPlayer].socket, buffer, sizeof(buffer), 0);
    // Assume we have a function that will broadcast a message to all players
    broadcast(game, buffer);
}

void closeSockets(Game* game) {
    for (int i = 0; i < game->numPlayers; i++) {
        close(game->players[i].socket);
    }
    close(game->serverSocket);
}
