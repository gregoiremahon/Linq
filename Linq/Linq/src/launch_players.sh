#!/bin/bash

# Port de départ pour les clients
start_port=32001

# Commande pour lancer un client
command="./linq localhost 32000 localhost"

# Boucle pour lancer 5 clients
for i in {1..5}
do
    # Générer un nom aléatoire en utilisant $RANDOM
    name="player$RANDOM"

    # Calculer le port du client
    port=$((start_port + i))

    # Construire la commande complète avec le nom et le port du client
    full_command="$command $port $name"

    # Lancer la commande dans une nouvelle fenêtre de terminal
    osascript -e "tell app \"Terminal\" to do script \"${full_command}\""
done
