#include "game.h"
#include "network.h"

int main() {
    // Start the server on port 12345
    int serverSocket = startServer(12345);

    // Initialize the game with 4 players
    Game game;
    initGame(&game, 4, serverSocket);

    // Wait for players to connect
    acceptConnections(&game);

    // The game loop
    for (int i = 0; i < game.numPlayers; i++) {
        assignRoles(&game);

        char* password = "example";
        sendPassword(&game, password);

        // Each player speaks twice
        for (int round = 0; round < 2; round++) {
            for (game.currentPlayer = 0; game.currentPlayer < game.numPlayers; game.currentPlayer++) {
                startTurn(&game);
                receiveWord(&game);
            }
        }

        // Voting process
        collectVotes(&game);

        // Evaluation of the round
        evaluateRound(&game);
    }

    // Clean up at the end
    closeSockets(&game);

    // Free memory
    free(game.players);

    return 0;
}
