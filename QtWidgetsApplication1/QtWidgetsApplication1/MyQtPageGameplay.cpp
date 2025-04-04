#include "MyQtPageGameplay.h"

MyQtPageGameplay::MyQtPageGameplay(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent)
    : MyQtPage(stack, G, manager, parent) {

}

void MyQtPageGameplay::refresh(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent)
{
    QWidget* pageGame = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(pageGame);

    QLabel* gameLabel = new QLabel(pageGame);
    gameLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(gameLabel);

    QLabel* titleLabel = new QLabel(pageGame);
    layout->addWidget(titleLabel);

    QLabel* ProgressionLabel = new QLabel(pageGame);
    layout->addWidget(ProgressionLabel);

    int pageIndex = stack->addWidget(pageGame); // Add the page and get its index
    qDebug() << "PageGame ajouté à l'index :" << pageIndex;

    QObject::connect(stack, &QStackedWidget::currentChanged, [stack, pageGame, G, gameLabel, titleLabel, ProgressionLabel, manager](int index) {
        qDebug() << "Index actuel changé à :" << index;
        if (stack->widget(index) == pageGame) {
            qDebug() << "PageGame est affichée!";
            G->gameStruct.chansonEnCours = new Chanson(CHANSON_2_MP3);
            G->demarrerPartie(gameLabel, titleLabel, ProgressionLabel, manager, nullptr, stack);
        }
        });
    stack->addWidget(pageGame);
}                                   //il manque changer dans ChangerDePage, ajouter QtManager* manager à l'appel de fct

void MyQtPageGameplay::setBackground()
{
}
