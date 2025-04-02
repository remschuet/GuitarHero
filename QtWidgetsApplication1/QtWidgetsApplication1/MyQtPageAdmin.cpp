#include "MyQtPageAdmin.h"

MyQtPageAdmin::MyQtPageAdmin(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent)
    : MyQtPage(stack, G, manager, parent)
{

}

void MyQtPageAdmin::refresh(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent)
{
    QWidget* window = new QWidget(parent);
    // window->setStyleSheet(QString("background-color: %1;").arg(COULEUR_FOND));
    QVBoxLayout* layout = new QVBoxLayout(window);
    // pageAdmin->setStyleSheet("background-color: #222; color: white;");


    // Zone de texte pour logs
    QTextEdit* logArea = new QTextEdit(window);
    logArea->setStyleSheet(
        "background-color: black; "
        "color: green; "
        "font-size: 18px; "
        "padding: 10px; "
        "border-radius: 10px;"
    );
    logArea->setReadOnly(true);
    logArea->setFixedHeight(200);
    layout->addWidget(logArea);

    // Entrées pour Key et Value
    QHBoxLayout* inputLayout = new QHBoxLayout();

    QLineEdit* keyInput = new QLineEdit(window);
    keyInput->setPlaceholderText("Key");
    keyInput->setStyleSheet(
        "QLineEdit { "
        "    background-color: #333; "
        "    color: white; "
        "    border-radius: 5px; "
        "    padding: 5px; "
        "    font-size: 18px; "
        "} "
    );

    QLineEdit* valueInput = new QLineEdit(window);
    valueInput->setPlaceholderText("Value");
    valueInput->setStyleSheet(
        "QLineEdit { "
        "    background-color: #333; "
        "    color: white; "
        "    border-radius: 5px; "
        "    padding: 5px; "
        "    font-size: 18px; "
        "} "
    );

    QPushButton* sendButton = new QPushButton("Envoyer", window);
    sendButton->setStyleSheet(
        "QPushButton { "
        "    background-color: blue; "
        "    color: white; "
        "    font-size: 18px; "
        "    border-radius: 5px; "
        "    padding: 5px 10px; "
        "} "
        "QPushButton:hover { "
        "    background-color: lightblue; "
        "    color: white; "
        "}"
    );

    inputLayout->addWidget(keyInput);
    inputLayout->addWidget(valueInput);
    inputLayout->addWidget(sendButton);
    layout->addLayout(inputLayout);

    // Bouton Retour
    QPushButton* btnRetour = new QPushButton("Retour", window);
    btnRetour->setFixedSize(120, 40);
    btnRetour->setStyleSheet(
        "QPushButton { "
        "    background-color: green; "
        "    color: white; "
        "    font-size: 20px; "
        "    border-radius: 5px; "
        "    padding: 5px 10px; "
        "    width: 50px;} "
        "QPushButton:hover { "
        "    background-color: gray; "
        "    color: white; "
        "}"
    );
    layout->addWidget(btnRetour);



    // Connexion du bouton "Envoyer" pour vider les entrées
    QObject::connect(sendButton, &QPushButton::clicked, [=]() {
        keyInput->clear();
        valueInput->clear();
        });

    // Connexion du bouton "Retour" pour revenir à la page précédente
    QObject::connect(btnRetour, &QPushButton::clicked, [=]() {
        stack->setCurrentIndex(0); // Exemple : revenir à la première page du stack
        });

    stack->addWidget(window);
}

void MyQtPageAdmin::setBackground() {
}
