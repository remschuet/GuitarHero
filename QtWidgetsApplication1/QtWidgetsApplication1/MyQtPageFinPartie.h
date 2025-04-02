#pragma once

#include "MyQtPage.h"

class MyQtPageFinPartie : public MyQtPage {
    Q_OBJECT
public:
    explicit MyQtPageFinPartie(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent = nullptr);
    void setBackground() override;
};