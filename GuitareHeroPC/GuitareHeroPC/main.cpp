#include "ComBluetooth.h"
#include "Gameplay.h"

int main() {
    const ComMode MODE = CLAVIER;
    const std::string NOM_PORT = "COM5";

    Gameplay gameplay(NOM_PORT, MODE);
    gameplay.SelectionJoueur();
    return 0;
}
