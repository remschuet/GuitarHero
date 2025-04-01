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

    const ComMode MODE = CLAVIER;
    const std::string NOM_PORT = "COM3";

    QStackedWidget stack;
    Gameplay* gameplay = new Gameplay(NOM_PORT, MODE);

    // Ajouter les fenêtres
    fenetres QtFenetre = Accueil;
    myQtManager::qtPageMenu(nullptr, &stack, gameplay);
    myQtManager::qtPageAccueil(nullptr, &stack, gameplay);
    myQtManager::qtPageMeilleurScore(nullptr, &stack, gameplay);
    myQtManager::qtPageInformations(nullptr, &stack, gameplay);
    myQtManager::qtPageParametres(nullptr, &stack, gameplay);
    myQtManager::qtPageGame(nullptr, &stack, gameplay);

    stack.setCurrentIndex(QtFenetre);
    stack.resize(TAILLE_ECRAN_X, TAILLE_ECRAN_Y);
    stack.show();

    /*int entier = 0;
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
    }*/

    return app.exec();
}

/*int main(int argc, char* argv[]) {    //main projet 1

    const ComMode MODE = CLAVIER;
    const std::string NOM_PORT = "COM3";

    Gameplay gameplay(NOM_PORT, MODE);
    gameplay.SelectionJoueur();
}*/