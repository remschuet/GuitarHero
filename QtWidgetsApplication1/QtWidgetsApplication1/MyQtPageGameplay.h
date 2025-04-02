#pragma once

#include "MyQtPage.h"

class MyQtPageGameplay : public MyQtPage {
    Q_OBJECT
public:
    explicit MyQtPageGameplay(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent = nullptr);
    static void refresh(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent = nullptr);

    void setBackground() override;
};