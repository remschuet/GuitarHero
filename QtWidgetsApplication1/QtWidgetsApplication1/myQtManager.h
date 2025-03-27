#pragma once
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include "Gameplay.h"
#include "GameStruct.h"
#include "CONST_QT.h"


enum fenetres { Menu, Accueil, MeilleursScores, Informations, FinPartie, Parametre};

class myQtManager {
public:
    static void myQt_setFont(QLabel* q, int tailleFont);

    static void qtPageInformations(QWidget* window, QStackedWidget* stack, Gameplay* G);

    static void qtPageMenu(QWidget* parent, QStackedWidget* stack, Gameplay* G);

    static void qtPageFinPartie(QWidget* window, QStackedWidget* stack, Gameplay* G);

    static void qtPageParametres(QWidget* window, QStackedWidget* stack, Gameplay* G);

    static void qtPageMeilleurScore(QWidget* window, QStackedWidget* stack, Gameplay* G);

    static void qtPageAccueil(QWidget* parent, QStackedWidget* stack, Gameplay* G);
};