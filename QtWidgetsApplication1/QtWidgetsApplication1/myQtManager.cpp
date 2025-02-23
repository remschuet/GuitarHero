#include "myQtManager.h"


void myQtManager::myQt_setFont(QLabel* q, int tailleFont) {
    // Créer un objet QFont et définir la taille de la police
    QFont font = q->font();
    font.setPointSize(tailleFont);

    // Appliquer la nouvelle police au QLabel
    q->setFont(font);
}

#include "myQtManager.h"

void myQtManager::qtPageInformations(QWidget* parent, QStackedWidget* stack) {
    QWidget* window = new QWidget();

    std::string nom = "bob";
    int score = 1230;

    window->setWindowTitle("Informations");

    // Titre
    QLabel* title = new QLabel("Informations", window);
    title->move(670, 30);

    // Pseudo et Score
    QLabel* pseudoLabel = new QLabel("<h3>Pseudo</h3>", window);
    QLabel* pseudoValue = new QLabel(QString::fromStdString(nom), window);
    QLabel* scoreLabel = new QLabel("<h3>Score</h3>", window);
    QLabel* scoreValue = new QLabel(QString::number(score, 10), window);

    pseudoLabel->move(50, 150);
    pseudoValue->move(150, 150);
    scoreLabel->move(50, 200);
    scoreValue->move(150, 200);

    // Bouton Retour
    QPushButton* backButton = new QPushButton("Retour", window);
    backButton->move(50, 400);

    // Changer de page au clic sur "Retour"
    QObject::connect(backButton, &QPushButton::clicked, [stack]() {
        stack->setCurrentIndex(0); // Retour au menu
        });

    stack->addWidget(window);
}

void myQtManager::qtPageMenu(QWidget* parent, QStackedWidget* stack) {
    QWidget* window = new QWidget();
    window->setWindowTitle("Menu");

    QPushButton* infoButton = new QPushButton("Voir Informations", window);
    infoButton->move(50, 50);

    // Changer de page au clic
    QObject::connect(infoButton, &QPushButton::clicked, [stack]() {
        stack->setCurrentIndex(1); // Aller à la page d'informations
        });

    stack->addWidget(window);
}

void myQtManager::qtPageFinPartie(QWidget* window)
{
}

void myQtManager::qtPageParametres(QWidget* window)
{
}

void myQtManager::qtPageMeilleurScore(QWidget* window)
{
}

