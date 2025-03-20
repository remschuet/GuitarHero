#include "ComBluetooth.h"
#include "Gameplay.h"

int main(int argc, char* argv[]) {

    const ComMode MODE = FILAIRE;
    const std::string NOM_PORT = "COM2";

    Gameplay gameplay(NOM_PORT, MODE);
    gameplay.SelectionJoueur();
   //  for (int i = 0; i < 30; i++) {
   //      gameplay.envoyerMsg("hello", "world");
//        Sleep(500);
  //   }
//     gameplay.SelectionJoueur();
}
