#pragma once
#include <QApplication>
#include <QWidget>
#include <QStackedLayout>
#include <QLabel>
#include <QScrollArea>
#include <QPixmap>
#include <qdebug.h>
#include <QStackedWidget>
#include <QInputDialog>
#include <QPushButton>
#include <Qdialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QComboBox>
#include "DAOSqlite.h"
#include "Gameplay.h"
#include "GameStruct.h"
#include "CONST_QT.h"
#include "Enum.h"
#include <cstdlib> 
#include <QStackedWidget>
#include <QProcess>

class Gameplay;

class myQtManager {
public:
    QLabel* getUnusedLabel();
	
    QWidget* getParentWidget();

    QLabel* getLabelForNote(const Note& note);

    static void myQt_setFont(QLabel* q, int tailleFont);

    static void changerDePage(QStackedWidget* stack, fenetres page, Gameplay* G, myQtManager* manager);

    static void qtPageInformations(QWidget* window, QStackedWidget* stack, Gameplay* G, myQtManager* manager);

    static void qtPageAdmin(QWidget* pageAdmin, QStackedWidget* stack, Gameplay* G, myQtManager* manager);

    void static crashAvecMessage(const QString& message, Gameplay* game);

    static void qtPageMenu(QWidget* parent, QStackedWidget* stack, Gameplay* G, myQtManager* manager);

    void qtPageFinPartie(Gameplay* game, QVBoxLayout* layoutGame, QStackedWidget* stack);

    static void qtPageParametres(QWidget* window, QStackedWidget* stack, Gameplay* G, myQtManager* manager);

    static void qtPageMeilleurScore(QWidget* window, QStackedWidget* stack, Gameplay* G, myQtManager* manager);

    static void qtPageGame(QWidget* window, QStackedWidget* stack, Gameplay* G, myQtManager* manager);

    static void qtPageAccueil(QWidget* parent, QStackedWidget* stack, Gameplay* G, myQtManager* manager);

    static void afficherImage(QWidget* parentWidget, const QString& imagePath);

    static void afficherPopupSelectionMusique(QWidget* parent, QStackedWidget* stack, Gameplay* G, myQtManager* manager);

    static void departMusiqueMenu();

    static void arretMusiqueMenu();


    QWidget* parentWidget;
	QList<QLabel*> labels;
    //static QWidget* pageGame;
    static QVBoxLayout* GlobalLayout;
    static std::string nomChanson;
};

