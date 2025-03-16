#include "ComBluetooth.h"
#include "Gameplay.h"

int main(int argc, char* argv[]) {

    HEAD
    const ComMode MODE = CLAVIER;
    const std::string NOM_PORT = "COM3";
=======
    const ComMode MODE = FILAIRE;
    const std::string NOM_PORT = "COM4";
    bc94005f0962e64506c9d6f025ef876112c1afe9

    Gameplay gameplay(NOM_PORT, MODE);
    gameplay.SelectionJoueur();
   //  for (int i = 0; i < 30; i++) {
   //      gameplay.envoyerMsg("hello", "world");
//        Sleep(500);
  //   }
//     gameplay.SelectionJoueur();
}
