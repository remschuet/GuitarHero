#pragma once
#include "Gameplay.h"
#include "myQtManager.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>

#include <QVBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QGraphicsOpacityEffect>
#include <QTextEdit>
#include <QListWidget>
#include <QFileDialog>
#include <QMenu>
#include <QString>
#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>
#include <iostream>

class MyQtPage : public QWidget {
    Q_OBJECT
public:
    explicit MyQtPage(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent = nullptr)
        : QWidget(parent), stack(stack), G(G), manager(manager) {
    }

    virtual void setBackground() = 0;  // Fonction virtuelle pure

    void myQt_setFont(QLabel* q, int tailleFont);

protected:
    QStackedWidget* stack;
    Gameplay* G;
    myQtManager* manager;
};

