#pragma once
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QStackedWidget>
#include <QPushButton>

#include "CONST_QT.h"

class myQtManager {
public:
    static void myQt_setFont(QLabel* q, int tailleFont);

    static void qtPageInformations(QWidget* parent, QStackedWidget* stack);
    static void qtPageMenu(QWidget* parent, QStackedWidget* stack);

    static void qtPageFinPartie(QWidget* window);

    static void qtPageParametres(QWidget* window);

    static void qtPageMeilleurScore(QWidget* window);

};

