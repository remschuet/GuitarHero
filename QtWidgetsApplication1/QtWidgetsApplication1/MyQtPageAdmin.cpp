#include "MyQtPageAdmin.h"

MyQtPageAdmin::MyQtPageAdmin(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent)
    : MyQtPage(stack, G, manager, parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    // Zone de texte pour logs
    QTextEdit* logArea = new QTextEdit(this);
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

    QLineEdit* keyInput = new QLineEdit(this);
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

    QLineEdit* valueInput = new QLineEdit(this);
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

    QPushButton* sendButton = new QPushButton("Envoyer", this);
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
    QPushButton* btnRetour = new QPushButton("Retour", this);
    btnRetour->setFixedSize(120, 40);
    btnRetour->setStyleSheet(
        "QPushButton { "
        "    background-color: green; "
        "    color: white; "
        "    font-size: 20px; "
        "    border-radius: 5px; "
        "    padding: 5px 10px; "
        "} "
        "QPushButton:hover { "
        "    background-color: gray; "
        "    color: white; "
        "}"
    );
    layout->addWidget(btnRetour);

    // Connexion du bouton "Envoyer" pour vider les entrées
    connect(sendButton, &QPushButton::clicked, [=]() {
        keyInput->clear();
        valueInput->clear();
        });

    // Connexion du bouton "Retour" pour revenir à la page précédente
    connect(btnRetour, &QPushButton::clicked, [=]() {
        stack->setCurrentIndex(0); // Exemple : revenir à la première page du stack
        });
}

void MyQtPageAdmin::setBackground()
{
}
