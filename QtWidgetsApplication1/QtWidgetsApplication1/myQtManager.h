#pragma once
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include "CONST_QT.h"

class myQtManager {
public:
    static void myQt_setFont(QLabel* q, int tailleFont);
    static void qtPageInformations(QWidget* window);

    static void qtPageFinPartie(QWidget* window);

    static void qtPageParametres(QWidget* window);

    static void qtPageMeilleurScore(QWidget* window);

    static void qtPageMenu(QWidget* window);
};

