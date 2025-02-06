#include "ComBluetooth.h"
#include "Gameplay.h"

/*
    FICHIER MAIN
*/


int main() {
    const ComMode MODE = CLAVIER;
    const std::string NOM_PORT = "COM5";

    Gameplay gameplay(NOM_PORT, MODE);
    gameplay.loopMenu();
    return 0;
}
