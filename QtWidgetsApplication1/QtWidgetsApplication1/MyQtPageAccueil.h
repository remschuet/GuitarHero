#pragma once

#include "MyQtPage.h"


class MyQtAccueil : public MyQtPage {
    Q_OBJECT
public:
    explicit MyQtAccueil(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent = nullptr);
    void setBackground() override;
};
