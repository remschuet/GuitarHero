#pragma once

#include "MyQtPage.h"

class MyQtPageInfoJoueur : public MyQtPage {
    Q_OBJECT
public:
    explicit MyQtPageInfoJoueur(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent = nullptr);
    static void refresh(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent = nullptr);
    void setBackground() override;
};