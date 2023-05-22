#include "game.h"
#include "network.h"

void initGame(Game* game, int numPlayers, int serverSocket) {
    game->numPlayers = numPlayers;
    game->serverSocket = serverSocket;
    game->players = (Player*) malloc(sizeof(Player) * numPlayers);
}

void assignRoles(Game* game) {
    // Here we randomly select two spies among the players
    srand(time(0));
    int spy1 = rand() % game->numPlayers;
    int spy2 = rand() % game->numPlayers;
    while(spy1 == spy2) {
        spy2 = rand() % game->numPlayers;
    }

    for (int i = 0; i < game->numPlayers; i++) {
        game->players[i].role = (i == spy1 || i == spy2) ? SPY : COUNTER_SPY;
    }
}

void startTurn(Game* game) {
    // Notify the current player that it's their turn
    send(game->players[game->currentPlayer].socket, "Your turn\n", 9, 0);
}

void collectVotes(Game* game) {
    char buffer[256];
    for (int i = 0; i < game->numPlayers; i++) {
        send(game->players[i].socket, "Vote for the spies\n", 19, 0);
        recv(game->players[i].socket, buffer, sizeof(buffer), 0);
        // Interpret the player's vote and update the game state accordingly
        int vote = atoi(buffer);
        game->players[vote].votes++;
    }
}

void evaluateRound(Game* game) {
    // Assuming we have a variable "points" for each player
    // Let's award points based on votes received
    for(int i = 0; i < game->numPlayers; i++) {
        game->players[i].points += game->players[i].votes;
    }
    // Reset votes after evaluation
    for(int i = 0; i < game->numPlayers; i++) {
        game->players[i].votes = 0;
    }
}
