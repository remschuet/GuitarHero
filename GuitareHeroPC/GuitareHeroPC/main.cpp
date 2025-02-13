#include "ComBluetooth.h"
#include "Gameplay.h"
#include "Camera.cpp"

/*
    FICHIER MAIN
*/


int main() 
{
    const ComMode MODE = CLAVIER;
    const std::string NOM_PORT = "COM5";
    afficherImage("Image joueur", "Icone.jpeg");

    Gameplay gameplay(NOM_PORT, MODE);
    gameplay.SelectionJoueur();
    return 0;
}
