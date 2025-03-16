#include "ComBluetooth.h"
#include "Gameplay.h"

int main(int argc, char* argv[]) {

    const ComMode MODE = FILAIRE;
    const std::string NOM_PORT = "COM5";

    Gameplay gameplay(NOM_PORT, MODE);
    for (int i = 0; i < 30; i++) {
        gameplay.envoyerMsg("hello", "world");
        Sleep(500);
    }
//     gameplay.SelectionJoueur();
}