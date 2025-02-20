#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "CONST_QT.h"
#include "QtHelper.h"
#include "myQtManager.h"


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    myQtManager::qtPageInformations(&window); // Appel de la fonction
    window.show(); // Afficher la fenêtre

    return app.exec();
}
