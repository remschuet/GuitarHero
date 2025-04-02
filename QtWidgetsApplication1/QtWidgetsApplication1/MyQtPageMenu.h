#pragma once

#include "MyQtPage.h"

class MyQtPageMenu : public MyQtPage {
    Q_OBJECT
public:
    explicit MyQtPageMenu(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent = nullptr);
    static void refresh(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent = nullptr);
    void setBackground() override;
};
