#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>
#include "Gameplay.h"
#include "myQtManager.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>

class MyQtPage : public QWidget {
    Q_OBJECT
public:
    explicit MyQtPage(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent = nullptr)
        : QWidget(parent), stack(stack), G(G), manager(manager) {
    }

    virtual void setBackground() = 0;  // Fonction virtuelle pure

protected:
    QStackedWidget* stack;
    Gameplay* G;
    myQtManager* manager;
};

