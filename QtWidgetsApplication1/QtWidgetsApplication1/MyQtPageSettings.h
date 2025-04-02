#pragma once

#include "MyQtPage.h"

class MyQtPageSettings : public MyQtPage {
    Q_OBJECT
public:
    explicit MyQtPageSettings(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent = nullptr);
    static void refresh(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent = nullptr);

    void setBackground() override;
};
