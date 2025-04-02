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
#include <QMainWindow>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    const ComMode MODE = CLAVIER;
    const std::string NOM_PORT = "COM3";

    // Création de la fenêtre principale
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Guitar Hero UDS");

    // Création du gestionnaire de pages
    QStackedWidget* stack = new QStackedWidget();

    // Initialisation du jeu
    Gameplay* gameplay = new Gameplay(NOM_PORT, MODE);

    // Ajouter les fenêtres
    fenetres QtFenetre = Accueil;
    // myQtManager::qtPageMenu(nullptr, stack, gameplay, nullptr);
    //myQtManager::qtPageAccueil(nullptr, stack, gameplay, nullptr);
    // myQtManager::qtPageMeilleurScore(nullptr, stack, gameplay, nullptr);
    // myQtManager::qtPageInformations(nullptr, stack, gameplay, nullptr);
    // myQtManager::qtPageParametres(nullptr, stack, gameplay, nullptr);
    //myQtManager::qtPageGame(nullptr, stack, gameplay, nullptr);
    // myQtManager::qtPageAdmin(nullptr, stack, gameplay, nullptr);

    // Définition de la fenêtre principale avec le stack
    mainWindow.setCentralWidget(stack);

    // Mode plein écran
    mainWindow.showFullScreen();

    // Définir la page d'accueil comme première page affichée
    stack->setCurrentIndex(Accueil);

    return app.exec();
}
/*int main(int argc, char* argv[]) {    //main projet 1

    const ComMode MODE = CLAVIER;
    const std::string NOM_PORT = "COM3";

    Gameplay gameplay(NOM_PORT, MODE);
    gameplay.SelectionJoueur();
}*/