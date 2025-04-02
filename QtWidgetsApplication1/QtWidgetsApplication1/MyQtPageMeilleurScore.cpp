#include "MyQtPageMeilleurScore.h"

MyQtPageMeilleurScore::MyQtPageMeilleurScore(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent)
    : MyQtPage(stack, G, manager, parent) {
    
}

void MyQtPageMeilleurScore::refresh(QStackedWidget* stack, Gameplay* G, myQtManager* manager, QWidget* parent)
{
    QWidget* pageMeilleursScores = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(pageMeilleursScores);
    mainLayout->setContentsMargins(20, 20, 20, 20); // Marge globale

    // Image de fond
    QLabel* backgroundLabel = new QLabel(pageMeilleursScores);
    backgroundLabel->setGeometry(0, 0, TAILLE_ECRAN_X, TAILLE_ECRAN_Y);
    QPixmap resizedPixmap("./images/meilleurscore.png");
    backgroundLabel->setPixmap(resizedPixmap);
    backgroundLabel->setScaledContents(true);
    backgroundLabel->lower(); // Assurer que l'image reste en arrière-plan

    // Titre "Meilleur Score"
    QLabel* titre = new QLabel("Meilleur Score");
    titre->setAlignment(Qt::AlignHCenter);
    QFont fontTitre("Arial", 20, QFont::Bold);
    titre->setFont(fontTitre);
    titre->setStyleSheet(COULEUR_FOND);
    mainLayout->addWidget(titre);

    // Espacement après le titre
    mainLayout->addSpacing(10);

    // Debug
    qDebug() << "qtPageMeilleurScore appelée\n";

    // Récupération des meilleurs scores
    std::pair<std::string, int> scores[10];
    DAOSqlite* sqlite = DAOSqlite::getInstance();
    sqlite->getMeilleurScore(scores);

    // Layout contenant la liste des scores
    QVBoxLayout* scoreLayout = new QVBoxLayout();
    scoreLayout->setSpacing(8); // Espacement entre chaque score

    // Affichage des scores
    for (size_t i = 0; i < 10; ++i) {
        if (scores[i].first != "") {
            QString medal, borderColor, nameBgColor, positionTextColor, textColor = COULEUR_TEXTE_BOUTON;

            if (i == 0) {
                medal = "🥇"; borderColor = "#FFD700"; nameBgColor = "#FFD700"; positionTextColor = "#FFD700"; textColor = "#FFD700";
            }
            else if (i == 1) {
                medal = "🥈"; borderColor = "#C0C0C0"; nameBgColor = "#C0C0C0"; positionTextColor = "#C0C0C0"; textColor = "#C0C0C0";
            }
            else if (i == 2) {
                medal = "🥉"; borderColor = "#CD7F32"; nameBgColor = "#CD7F32"; positionTextColor = "#CD7F32"; textColor = "#CD7F32";
            }
            else {
                nameBgColor = COULEUR_TEXTE_BOUTON; positionTextColor = "#000000";
            }

            // Cadre contenant un score
            QFrame* scoreCard = new QFrame();
            scoreCard->setStyleSheet("background-color: rgba(128, 128, 128, 0.5); "
                "border: 2px solid " + borderColor + "; "
                "border-radius: 10px; "
                "padding: 5px;");
            scoreCard->setFixedHeight(50);

            QHBoxLayout* rowLayout = new QHBoxLayout(scoreCard);
            rowLayout->setContentsMargins(10, 5, 10, 5);

            // Position + Médaille
            QLabel* position = new QLabel(QString::number(i + 1) + ". " + medal);
            position->setFixedWidth(50);
            position->setStyleSheet("font-weight: bold; color: " + positionTextColor + ";");
            rowLayout->addWidget(position);

            // Nom du joueur
            QLabel* nomJoueur = new QLabel(QString::fromStdString(scores[i].first));
            nomJoueur->setFixedWidth(150);
            nomJoueur->setFixedHeight(30);
            nomJoueur->setStyleSheet("font-weight: bold; color: #000000; "
                "background-color: " + nameBgColor + "; "
                "border-radius: 5px; "
                "padding: 5px;");
            rowLayout->addWidget(nomJoueur);

            // Score
            QLabel* score = new QLabel(QString::number(scores[i].second));
            score->setFixedWidth(60);
            score->setStyleSheet("font-weight: bold; color: " + textColor + ";");
            rowLayout->addWidget(score);

            scoreLayout->addWidget(scoreCard);
        }
    }

    mainLayout->addLayout(scoreLayout);

    // Espacement avant le bouton retour
    mainLayout->addSpacing(15);

    // Bouton retour aligné en bas à droite
    QPushButton* btnRetour = new QPushButton("Retour");
    btnRetour->setStyleSheet("background-color: red; color: white; padding: 5px 10px;");
    btnRetour->setFixedSize(100, 40);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(btnRetour);

    mainLayout->addLayout(btnLayout);

    // Action du bouton retour
    QObject::connect(btnRetour, &QPushButton::clicked, [stack]() {
        stack->setCurrentIndex(Menu);
        });

    pageMeilleursScores->setLayout(mainLayout);
    stack->addWidget(pageMeilleursScores);

}

void MyQtPageMeilleurScore::setBackground()
{
}
