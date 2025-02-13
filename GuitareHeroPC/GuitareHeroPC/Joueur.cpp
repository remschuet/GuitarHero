#include "Joueur.h"
#include <DAOSqlite.h>

Joueur::Joueur(std::string nom, int MeilleurScore, std::string image, int score)
{
	nomJoueur = nom;
	Icone = image;
	ScoreMax = MeilleurScore;
	ScoreActuel = score;
}

Joueur::~Joueur() {

}

bool Joueur::setNouveauNomJoueur(std::string NouveauNom) {
	DAOSqlite* sqlite = DAOSqlite::getInstance();
	bool retour = sqlite->updateJoueur(nomJoueur, NouveauNom);

	if (retour) {
		Joueur* j = sqlite->getJoueur(NouveauNom);
		this->nomJoueur = j->getNomJoueur();
	}

	return retour;
}

bool Joueur::setMeilleurScore(int ScoreMax, int ScoreActuel)
{
	return false;
}

std::string Joueur::getNomJoueur()
{
	return nomJoueur;
}

int Joueur::getMeilleurScore() {
	return ScoreMax;
}

std::string Joueur::getImage() {
	return Icone;
}

int Joueur::ScorePartie(int ScoreActuel, int augmentation)
{
	//augmentation = nbr de pts de plus lors de la partie
	ScoreActuel += augmentation;
	return ScoreActuel;
}

void Joueur::setNouvelleImage(std::string imagePath) {
	DAOSqlite* sqlite = DAOSqlite::getInstance();
	bool retour = sqlite->updateImageJoueur(nomJoueur, imagePath);

	if (retour) {
		Joueur* j = sqlite->getJoueur(nomJoueur);
		this->Icone = j->getImage();
	}
}
