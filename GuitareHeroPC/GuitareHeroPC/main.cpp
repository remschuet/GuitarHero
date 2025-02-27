#include "ComBluetooth.h"
#include "Gameplay.h"

int main(int argc, char* argv[]) {

    const ComMode MODE = CLAVIER;
    const std::string NOM_PORT = "COM3";

    Gameplay gameplay(NOM_PORT, MODE);
    gameplay.SelectionJoueur();
}