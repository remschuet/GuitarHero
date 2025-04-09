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
#include <QStackedWidget>
#include <QProcess>

#include "MyQtPageMenu.h"
#include "MyQtPageAdmin.h"
#include "MyQtPageMenu.h"
#include "MyQtPageInfoJoueur.h"
#include "MyQtPageAccueil.h"
#include "MyQtPageMeilleurScore.h"
#include "MyQtPageSettings.h"
#include "MyQtPageFinPartie.h"
#include "MyQtPageGameplay.h"


void siRelance(Gameplay* game, string nomJoueur) {
    DAOSqlite* sqlite = DAOSqlite::getInstance();
    game->gameStruct.joueur = sqlite->getJoueur(nomJoueur);
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    const ComMode MODE = FILAIRE;
    const std::string NOM_PORT = "COM3";

    // Création de la fenêtre principale
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Guitar Hero UDS");

    // Création du gestionnaire de pages
    QStackedWidget* stack = new QStackedWidget();

    // Initialisation du jeu
    Gameplay* gameplay = new Gameplay(NOM_PORT, MODE);

    // Ajouter les fenêtres
    myQtManager::qtPageMenu(nullptr, stack, gameplay, nullptr);
    myQtManager::qtPageAccueil(nullptr, stack, gameplay, nullptr);
    myQtManager::qtPageMeilleurScore(nullptr, stack, gameplay, nullptr);
    myQtManager::qtPageGame(nullptr, stack, gameplay, nullptr);

    MyQtPageSettings::refresh(stack, gameplay, nullptr);
    MyQtPageAdmin::refresh(stack, gameplay, nullptr);
    MyQtPageInfoJoueur::refresh(stack, gameplay, nullptr);

    mainWindow.setCentralWidget(stack);
    mainWindow.showFullScreen();


    // Vérifie si on a été relancé avec un message
    QStringList args = QCoreApplication::arguments();
    QString relanceMessage;
    if (args.size() > 1) {
        relanceMessage = args[1];
        qDebug() << "Application relancée avec message :" << relanceMessage;
    }
    // Choix de la page d'accueil : Menu si relancé, sinon Accueil
    if (!relanceMessage.isEmpty()) {
        gameplay->demarrerMusiqueJo(MUSIQUEMENU);
        siRelance(gameplay, relanceMessage.toStdString());
        stack->setCurrentIndex(Menu);
    }
    else {
        gameplay->demarrerMusiqueJo(MUSIQUEMENU);
        stack->setCurrentIndex(Accueil);
      
    }

    return app.exec();
}