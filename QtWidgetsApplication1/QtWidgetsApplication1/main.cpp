#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "CONST_QT.h"
#include "QtHelper.h"
#include "myQtManager.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QStackedWidget stack;

    // Ajouter les fenêtres
    myQtManager::qtPageMenu(nullptr, &stack);
    myQtManager::qtPageInformations(nullptr, &stack);

    stack.setCurrentIndex(0); // Afficher la première page (Menu)
    stack.show();

    return app.exec();
}
#include "ComBluetooth.h"
#include "Gameplay.h"

/*int main(int argc, char* argv[]) {

    const ComMode MODE = CLAVIER;
    const std::string NOM_PORT = "COM3";

    Gameplay gameplay(NOM_PORT, MODE);
    gameplay.SelectionJoueur();
}*/