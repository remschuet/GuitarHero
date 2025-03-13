#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "CONST_QT.h"
#include "QtHelper.h"
#include "myQtManager.h"
#include "ComBluetooth.h"
#include "Gameplay.h"
#include <QThread>
#include <QDebug>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QStackedWidget stack;

    // Ajouter les fenêtres
    myQtManager::qtPageMenu(nullptr, &stack);
    myQtManager::qtPageInformations(nullptr, &stack);

    stack.setCurrentIndex(0); // Afficher la première page (Menu)
    stack.resize(1920, 1080);
    stack.show();

    const ComMode MODE = CLAVIER;
    const std::string NOM_PORT = "COM3";
    
    int entier = 0;
    qDebug() << "debug entier actuel: " << entier;

    while (entier < 10) {
        // Exécuter la logique de votre jeu ici
        entier++;
        qDebug() << "debug entier actuel: " << entier;
        cout << "cout entier actuel: " << entier;

        // Traiter les événements Qt pour permettre les rafraîchissements
        QApplication::processEvents();

        // Pour éviter une boucle infinie sans délai
        QThread::msleep(10);
    }

    // Gameplay gameplay(NOM_PORT, MODE);
    // gameplay.SelectionJoueur();

    return app.exec();
}

/*int main(int argc, char* argv[]) {    //main projet 1

    const ComMode MODE = CLAVIER;
    const std::string NOM_PORT = "COM3";

    Gameplay gameplay(NOM_PORT, MODE);
    gameplay.SelectionJoueur();
}*/