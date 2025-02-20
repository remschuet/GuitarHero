#include "myQtManager.h"


void myQtManager::myQt_setFont(QLabel* q, int tailleFont) {
    // Créer un objet QFont et définir la taille de la police
    QFont font = q->font();
    font.setPointSize(tailleFont);

    // Appliquer la nouvelle police au QLabel
    q->setFont(font);
}

void myQtManager::qtPageInformations(QWidget* window) {
    std::string nom = "bob";
    int score = 1230;

    window->setWindowTitle("Informations");
    window->resize(TAILLE_ECRAN_X, TAILLE_ECRAN_Y); // Taille plus grande


    // Titre
    QLabel* title = new QLabel("Informations", window);
    QFont font;
    font.setPointSize(QT_TITLE);
    title->setFont(font);
    title->adjustSize();

    // Pseudo et Score
    QLabel* pseudoLabel = new QLabel("<h3>Pseudo</h3>", window);
    myQt_setFont(pseudoLabel, QT_SUBTITLE);
    QLabel* pseudoValue = new QLabel(QString::fromStdString(nom), window);
    QLabel* scoreLabel = new QLabel("<h3>Score</h3>", window);
    QLabel* scoreValue = new QLabel(QString::number(score, 10), window);

    title->move(670, 30);
    pseudoLabel->move(50, 150);
    pseudoValue->move(150, 150);
    // pseudoLabel->setFont(30);
    scoreLabel->move(50, 200);
    scoreValue->move(150, 200);

    // Avatar
    QLabel* avatar = new QLabel(window);
    avatar->setFixedSize(120, 120);
    avatar->setStyleSheet("border: 3px solid black; background-color: lightgray;");
    avatar->move(350, 150); // Positionner l'avatar

    // Boutons
    QPushButton* modifyButton = new QPushButton("Modifier", window);
    QPushButton* backButton = new QPushButton("Retour", window);

    modifyButton->move(50, 400);
    backButton->move(150, 400);
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

void myQtManager::qtPageMenu(QWidget* window)
{
}
