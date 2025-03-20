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

class myQtManager {
public:
    static void myQt_setFont(QLabel* q, int tailleFont);

    static void qtPageInformations(QWidget* parent, QStackedWidget* stack);

    static void qtPageMenu(QWidget* parent, QStackedWidget* stack, Gameplay* G);

    static void qtPageFinPartie(QWidget* window);

    static void qtPageParametres(QWidget* window);

    static void qtPageMeilleurScore(QWidget* window);

    static void qtPageAccueil(QWidget* parent, QStackedWidget* stack, Gameplay* G);
};