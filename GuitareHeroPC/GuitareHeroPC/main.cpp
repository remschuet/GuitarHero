#include "ComBluetooth.h"
#include "Gameplay.h"
/*
    FICHIER MAIN
*/


int main() {
    const bool EST_BLUETOOTH = false;
    const std::string NOM_PORT = "COM5";

    Gameplay gameplay(NOM_PORT, EST_BLUETOOTH);
    gameplay.loopMenu();
    return 0;
}
