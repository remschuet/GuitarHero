#include "MyQtPageInfoJoueur.h"

MyQtPageInfoJoueur::MyQtPageInfoJoueur(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent)
    : MyQtPage(stack, G, manager, parent) {

}

void MyQtPageInfoJoueur::refresh(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent)
{
    QWidget* window = new QWidget();

    // Image de fond
    QLabel* backgroundLabel = new QLabel(window);
    backgroundLabel->setGeometry(-275, -50, TAILLE_ECRAN_X, TAILLE_ECRAN_Y);
    QPixmap pixmap("./Images/placeholder_background_login.png");
    backgroundLabel->setPixmap(pixmap);
    backgroundLabel->setAlignment(Qt::AlignCenter);

    QGraphicsBlurEffect* blurEffect = new QGraphicsBlurEffect();
    blurEffect->setBlurRadius(10);
    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect();
    opacityEffect->setOpacity(0.7);
    backgroundLabel->setGraphicsEffect(opacityEffect);
    blurEffect->setParent(backgroundLabel);
    backgroundLabel->setGraphicsEffect(blurEffect);
    backgroundLabel->lower();

    QWidget* infoContainer = new QWidget(window);
    infoContainer->setGeometry(0, 0, TAILLE_ECRAN_X, TAILLE_ECRAN_Y);
    infoContainer->setStyleSheet("background-color: rgba(0, 0, 0, 100);");
    infoContainer->lower();

    QWidget* Box = new QWidget(window);
    Box->setStyleSheet("background-color: rgba(0, 0, 0, 150); border-radius: 25px; padding: 20px;");
    Box->setFixedSize(1100, 700);

    QVBoxLayout* BoxLayout = new QVBoxLayout(Box);
    BoxLayout->setAlignment(Qt::AlignCenter);
    BoxLayout->setSpacing(15);

    std::string nom = "Inconnu";
    int score = 0;
    QString imagePath = "./images/avatar.jpg";
    Joueur* joueurlog = G->getJoueur();

    if (joueurlog != nullptr) {
        nom = joueurlog->getNomJoueur();
        QString tempImagePath = QString::fromStdString(joueurlog->getImage());
        if (!tempImagePath.isEmpty() && QFile::exists(tempImagePath)) {
            imagePath = tempImagePath;
        }
        score = joueurlog->getMeilleurScore();
    }

    // Nouveau layout pour le titre "Informations"
    QHBoxLayout* titreLayout = new QHBoxLayout();
    titreLayout->setAlignment(Qt::AlignCenter); // Pour le centrer, mettre Qt::AlignHCenter

    QLabel* titreLabel = new QLabel("Informations", infoContainer);
    titreLabel->setStyleSheet("color: white; "
        "font-size: 40px; "
        "font-weight: bold; "
        "text-transform: uppercase; "
        "letter-spacing: 3px; "
        "text-shadow: 3px 3px 5px rgba(0, 0, 0, 0.8); "
        "border: none; "
        "padding: 10px; "
        "background: linear-gradient(to right, #ff0000, #ff6600, #ffff00, #33cc33, #0099ff, #9900cc); "
        "border-radius: 10px;");

    titreLayout->addWidget(titreLabel);
    BoxLayout->addLayout(titreLayout);  // On ajoute le titre avant le contenu

    // Layout principal contenant nom/score/photo
    QHBoxLayout* topContentLayout = new QHBoxLayout();
    topContentLayout->setAlignment(Qt::AlignTop);

    QVBoxLayout* leftLayout = new QVBoxLayout();
    leftLayout->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout* nameLayout = new QHBoxLayout();
    QLabel* pseudoValue = new QLabel(QString::fromStdString(nom), infoContainer);
    myQt_setFont(pseudoValue, QT_SUBTITLE);
    pseudoValue->setStyleSheet(QString("color: %1; font-weight: bold;").arg(COULEUR_TEXTE));
    pseudoValue->setFixedSize(500, 100);

    QPushButton* modiferNomJoueur = new QPushButton("✏️", infoContainer);
    modiferNomJoueur->setStyleSheet(QString(
        "background-color: %1; color: %2; border: 2px solid %3; padding: 5px; border-radius: 5px; font-size: 16px;"
    ).arg(COULEUR_BOUTON).arg(COULEUR_TEXTE_BOUTON).arg(COULEUR_PSEUDO_SCORE));
    modiferNomJoueur->setFixedSize(60, 60);

    QObject::connect(modiferNomJoueur, &QPushButton::clicked, [=]() {
        bool ok;
        QString nouveauNom = QInputDialog::getText(window, "Modifier le nom du joueur",
            "Entrez le nouveau nom du joueur :", QLineEdit::Normal, "", &ok);
        if (ok && !nouveauNom.isEmpty()) {
            if (joueurlog != nullptr) {
                joueurlog->setNouveauNomJoueur(nouveauNom.toStdString());
                pseudoValue->setText(nouveauNom);
                QMessageBox::information(window, "Nom modifié", "Le nom du joueur a été modifié avec succès.");
            }
        }
        else {
            QMessageBox::warning(window, "Nom invalide", "Le nom entré est invalide ou vide.");
        }
        });

    nameLayout->addWidget(pseudoValue);
    nameLayout->addWidget(modiferNomJoueur);

    QHBoxLayout* scoreLayout = new QHBoxLayout();
    QLabel* scoreValue = new QLabel("Score Max : " + QString::number(score), infoContainer);
    myQt_setFont(scoreValue, QT_SUBTITLE);
    scoreValue->setStyleSheet(QString("color: %1; font-weight: bold;").arg(COULEUR_TEXTE));
    scoreValue->setFixedSize(500, 100);
    scoreLayout->addWidget(scoreValue);
    scoreLayout->setAlignment(Qt::AlignLeft);

    leftLayout->addLayout(nameLayout);
    leftLayout->addSpacerItem(new QSpacerItem(0, nameLayout->sizeHint().height() - scoreLayout->sizeHint().height(), QSizePolicy::Minimum, QSizePolicy::Fixed));
    leftLayout->addLayout(scoreLayout);

    QVBoxLayout* rightLayout = new QVBoxLayout();
    rightLayout->setContentsMargins(0, 0, 0, 0);

    rightLayout->addSpacerItem(new QSpacerItem(0, pseudoValue->height() / 2, QSizePolicy::Minimum, QSizePolicy::Fixed));

    QLabel* imageLabel = new QLabel(infoContainer);
    QPixmap pixmap_profil(imagePath);
    const int PHOTO_SIZE = 300;
    if (!pixmap_profil.isNull()) {
        imageLabel->setPixmap(pixmap_profil.scaled(PHOTO_SIZE, PHOTO_SIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else {
        imageLabel->setText("Image non disponible");
    }
    imageLabel->setFixedSize(PHOTO_SIZE, PHOTO_SIZE);
    imageLabel->setAlignment(Qt::AlignTop);

    QPushButton* modifyButton = new QPushButton("✏️", infoContainer);
    modifyButton->setStyleSheet(QString(
        "background-color: %1; color: %2; border: 2px solid %3; padding: 5px; border-radius: 5px; font-size: 17px;"
    ).arg(COULEUR_BOUTON).arg(COULEUR_TEXTE_BOUTON).arg(COULEUR_PSEUDO_SCORE));
    modifyButton->setFixedSize(60, 60);

    QMenu* menu = new QMenu(modifyButton);
    menu->setStyleSheet(R"(
        QMenu {
            background-color: #333333;
            border: 2px solid #0078D7;
            padding: 5px;
        }
        QMenu::item {
            background-color: #444444;
            color: white;
            padding: 8px 20px;
            border-radius: 4px;
        }
        QMenu::item:selected {
            background-color: #00A759;
            color: white;
        }
    )");

    QAction* actionDefaultImage = new QAction("Mettre image par défaut", menu);
    QAction* actionTakePhoto = new QAction("Prendre une photo", menu);
    menu->addAction(actionDefaultImage);
    menu->addAction(actionTakePhoto);
    menu->setFixedWidth(500);

    QObject::connect(modifyButton, &QPushButton::clicked, [menu, modifyButton]() {
        QPoint globalPos = modifyButton->mapToGlobal(QPoint(0, modifyButton->height()));
        menu->exec(globalPos);
        });

    QObject::connect(actionDefaultImage, &QAction::triggered, [G, imageLabel]() {
        if (G && G->getJoueur()) {
            std::string defaultImagePath = "./images/avatar.jpeg";
            G->getJoueur()->setNouvelleImage();
            QPixmap newPixmap(QString::fromStdString(defaultImagePath));
            if (!newPixmap.isNull()) {
                imageLabel->setPixmap(newPixmap.scaled(300, 300, Qt::KeepAspectRatio));
            }
        }
        });

    QObject::connect(actionTakePhoto, &QAction::triggered, [G, imageLabel]() {
        if (G) {
            G->PrendreImage();
            if (G->getJoueur()) {
                QString newImagePath = QString::fromStdString(G->getJoueur()->getImage());
                QPixmap newPixmap(newImagePath);
                if (!newPixmap.isNull()) {
                    imageLabel->setPixmap(newPixmap.scaled(300, 300, Qt::KeepAspectRatio));
                }
            }
        }
        });

    rightLayout->addWidget(imageLabel, 0, Qt::AlignTop);
    rightLayout->addWidget(modifyButton, 0, Qt::AlignCenter);

    topContentLayout->addLayout(leftLayout);
    topContentLayout->addSpacing(20);
    topContentLayout->addLayout(rightLayout);

    // Ajouter le contenu principal après le titre
    BoxLayout->addLayout(topContentLayout);
    BoxLayout->addSpacing(40);

    QPushButton* backButton = new QPushButton("Retour", infoContainer);
    backButton->setStyleSheet(QString(
        "background-color: red; color: white; border: 2px solid red; padding: 10px; border-radius: 10px; font-size: 18px; font-weight: bold;"
    ));
    backButton->setFixedSize(150, 75);

    QObject::connect(backButton, &QPushButton::clicked, [stack]() {
        stack->setCurrentIndex(Menu);
        });

    BoxLayout->addWidget(backButton, 0, Qt::AlignCenter);

    QVBoxLayout* windowLayout = new QVBoxLayout(window);
    windowLayout->addStretch();
    windowLayout->addWidget(Box, 0, Qt::AlignCenter);
    windowLayout->addStretch();

    stack->addWidget(window);
}

void MyQtPageInfoJoueur::setBackground()
{
}
