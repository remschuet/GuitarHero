#include "MyQtPageSettings.h"
#include "MyQtManager.h"
#include <qDebug>
#include <conio.h>

MyQtPageSettings::MyQtPageSettings(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent)
    : MyQtPage(stack, G, manager, parent) {

}

void MyQtPageSettings::refresh(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent)
{
    // Créer un widget pour la page des paramètres
    QWidget* pageParametre = new QWidget();

    // Image de fond (comme dans qtPageMenu)
    QLabel* backgroundLabel = new QLabel(pageParametre);
    backgroundLabel->setGeometry(-190, -50, TAILLE_ECRAN_X, TAILLE_ECRAN_Y);
    QPixmap pixmap("./Images/placeholder_background_login.png");
    backgroundLabel->setPixmap(pixmap);
    backgroundLabel->setAlignment(Qt::AlignCenter);

    // Appliquer un effet de flou
    QGraphicsBlurEffect* blurEffect = new QGraphicsBlurEffect();
    blurEffect->setBlurRadius(10); // Ajustez le rayon de flou (5-20 pour un effet léger à fort)

    // Appliquer une opacité
    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect();
    opacityEffect->setOpacity(0.7); // Opacité de 0 (transparent) à 1 (opaque), ici 70% d'opacité

    // Combiner les effets : d'abord l'opacité, puis le flou
    backgroundLabel->setGraphicsEffect(opacityEffect);
    blurEffect->setParent(backgroundLabel); // Nécessaire pour que l'effet soit appliqué après l'opacité
    backgroundLabel->setGraphicsEffect(blurEffect);

    backgroundLabel->lower();

    // Ajouter une couche semi-transparente au-dessus de l'image
    QWidget* overlay = new QWidget(pageParametre);
    overlay->setGeometry(0, 0, TAILLE_ECRAN_X, TAILLE_ECRAN_Y);
    overlay->setStyleSheet("background-color: rgba(0, 0, 0, 100);");
    overlay->lower();

    // Conteneur central pour les paramètres
    QWidget* settingsBox = new QWidget(pageParametre);
    settingsBox->setStyleSheet("background-color: rgba(0, 0, 0, 150); border-radius: 25px; padding: 20px;");
    settingsBox->setFixedSize(600, 400);

    // Layout spécifique pour la boîte des paramètres
    QVBoxLayout* settingsBoxLayout = new QVBoxLayout(settingsBox);
    settingsBoxLayout->setAlignment(Qt::AlignCenter);
    settingsBoxLayout->setSpacing(15);

    // Titre des paramètres
    QLabel* titre = new QLabel("Paramètres", settingsBox);
    myQt_setFont(titre, 40);
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet(
        "color: white; "
        "font-size: 40px; "
        "font-weight: bold; "
        "text-transform: uppercase; "
        "letter-spacing: 3px; "
        "text-shadow: 3px 3px 5px rgba(0, 0, 0, 0.8); "
        "border: none; "
        "padding: 10px; "
        "background: linear-gradient(to right, #ff0000, #ff6600, #ffff00, #33cc33, #0099ff, #9900cc); "
        "border-radius: 10px;");
    settingsBoxLayout->addWidget(titre);

    // Liste des boutons (remplacement de "Difficulté" par "Langue")
    QStringList buttonNames = { "Langue 🈴", "Manette", "Mode Admin" }; // "Difficulté" changé en "Langue"
    QVector<QPushButton*> buttons;

    for (const QString& name : buttonNames) {
        QPushButton* button = new QPushButton(name, settingsBox);
        button->setStyleSheet(
            "QPushButton { "
            "    background-color: " + COULEUR_BOUTON + "; "
            "    color: white; "
            "    font-size: 25px; "
            "    border-radius: 5px; "
            "    padding: 5px 10px; "
            "}"
            "QPushButton:hover { "
            "    background-color: gray; "
            "    color: white; "
            "}"
        );
        button->setFixedSize(250, 50);
        buttons.append(button);
        settingsBoxLayout->addWidget(button, 0, Qt::AlignCenter);
    }

    // Bouton Retour
    QPushButton* backButton = new QPushButton("Retour", settingsBox);
    backButton->setStyleSheet(
        "QPushButton { "
        "    background-color: red; "
        "    color: white; "
        "    font-size: 25px; "
        "    border-radius: 5px; "
        "    padding: 5px 10px; "
        "} "
        "QPushButton:hover { "
        "    background-color: darkred; "
        "}"
    );
    backButton->setFixedSize(250, 50);
    settingsBoxLayout->addWidget(backButton, 0, Qt::AlignCenter);

    // Ajouter la boîte centrée dans la page
    QVBoxLayout* mainLayout = new QVBoxLayout(pageParametre);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addStretch();
    mainLayout->addWidget(settingsBox, 0, Qt::AlignCenter);
    mainLayout->addStretch();
    pageParametre->setLayout(mainLayout);

    // Connexion du bouton "Langue" pour afficher un pop-up
    QObject::connect(buttons[0], &QPushButton::clicked, [=]() {
        QMessageBox::information(parent, "Langue", "T'abuses"); // Pop-up avec "Abuses"
        });

    QObject::connect(buttons[2], &QPushButton::clicked, [=]() {
        qDebug("Admin mode ON.");
        while (!_kbhit()) {

            std::string msg;
            if (G->comArduino->recevoirMessage(msg)) {
                try {
                    json j = json::parse(msg);
                    qDebug().noquote() << QString::fromStdString(json::parse(msg).dump());
                }
                catch (const std::exception& e) {
					qDebug() << "Erreur JSON:" << e.what();
                    // qWarning() << "Erreur JSON:" << e.what();
                }
            }
            Sleep(250);
            QCoreApplication::processEvents();
        }
        qDebug() << "Admin mode OFF.";
        });
    // Connexion du bouton Retour
    QObject::connect(backButton, &QPushButton::clicked, [=]() {
        stack->setCurrentIndex(0);
        });

    // Ajouter la page au QStackedWidget
    stack->addWidget(pageParametre);
}
void MyQtPageSettings::setBackground()
{
}
