#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <time.h>

typedef enum {SPY, COUNTER_SPY} Role;

typedef struct {
    int socket;
    Role role;
    int votes;
    int points;
} Player;

typedef struct {
    int numPlayers;
    Player* players;
    int currentPlayer;
    int serverSocket;
} Game;

void initGame(Game* game, int numPlayers, int serverSocket);
void assignRoles(Game* game);
void startTurn(Game* game);
void collectVotes(Game* game);
void evaluateRound(Game* game);

#endif // GAME_H
