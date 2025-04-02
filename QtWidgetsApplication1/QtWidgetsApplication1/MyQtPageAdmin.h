#pragma once

#include "MyQtPage.h"

class MyQtPageAdmin : public MyQtPage {
    Q_OBJECT
public:
    explicit MyQtPageAdmin(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent = nullptr);
    static void refresh(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent = nullptr);
    void setBackground() override;
};