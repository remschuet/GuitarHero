#pragma once

#include "MyQtPage.h"

class MyQtPageMeilleurScore : public MyQtPage {
    Q_OBJECT
public:
    explicit MyQtPageMeilleurScore(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent = nullptr);
    void setBackground() override;
};
