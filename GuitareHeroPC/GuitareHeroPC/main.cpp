#include "ComBluetooth.h"
#include "Gameplay.h"

int main() {
    const ComMode MODE = BLUETOOTH;
    const std::string NOM_PORT = "COM3";

    Gameplay gameplay(NOM_PORT, MODE);
    gameplay.SelectionJoueur();
    return 0;
}
