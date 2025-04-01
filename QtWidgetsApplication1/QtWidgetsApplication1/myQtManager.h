#pragma once
#include <QApplication>
#include <QWidget>
#include <QStackedLayout>
#include <QLabel>
#include <QPixmap>
#include <qdebug.h>
#include <QStackedWidget>
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

class Gameplay;

class myQtManager {
public:
    static void myQt_setFont(QLabel* q, int tailleFont);

    static void changerDePage(QStackedWidget* stack, fenetres page, Gameplay* G, myQtManager* manager);

    static void qtPageInformations(QWidget* window, QStackedWidget* stack, Gameplay* G, myQtManager* manager);

    static void qtPageAdmin(QWidget* pageAdmin, QStackedWidget* stack, Gameplay* G, myQtManager* manager);

    static void qtPageMenu(QWidget* parent, QStackedWidget* stack, Gameplay* G, myQtManager* manager);

    static void qtPageFinPartie(QWidget* window, QStackedWidget* stack, Gameplay* G);

    static void qtPageParametres(QWidget* window, QStackedWidget* stack, Gameplay* G, myQtManager* manager);

    static void qtPageMeilleurScore(QWidget* window, QStackedWidget* stack, Gameplay* G, myQtManager* manager);

    static void qtPageGame(QWidget* window, QStackedWidget* stack, Gameplay* G, myQtManager* manager);

    static void qtPageAccueil(QWidget* parent, QStackedWidget* stack, Gameplay* G, myQtManager* manager);

    static void afficherImage(QWidget* parentWidget, const QString& imagePath);

};