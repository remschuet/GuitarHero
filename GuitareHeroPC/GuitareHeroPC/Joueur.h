#pragma once
#include "iostream"

class Joueur
{
public:
	std::string nomJoueur;
	std::string Icone = "";
	int ScoreMax = 0;
	int ScoreActuel = 0;

	//meilleur score et score actuel. Avec fct qui permet de faire une valeur += pour améliorer la valeur actuel lors de la partie
public:
	Joueur(std::string nom, int MeilleurScore = 0, std::string image = "DefaultJoueur.png", int score = 0);
	~Joueur();

	//fct modifier nom lorsqu'on est dans la page Joueur ( avec les infos du joueur )
	//fct NomUnique (S'assurer lors de la création du joueur que le nom n'est pas déjà pris)
	//fct Augmenter score pendant la partie
	//fct BetterScore (Est-ce que ScoreActuel est meilleur que ScoreMax à la fin de la partie)

	bool setNouveauNomJoueur(std::string AncienNom, std::string NouveauNom);	//True -> le nouveau nom est unique et a été modifié
	bool setMeilleurScore(int ScoreMax, int ScoreActuel);						//True -> le meilleur score a été modifié si le scoreActuel est > que le scoreMax

	std::string getNomJoueur(std::string nomJoueur);
	int getMeilleurScore(int ScoreMax);

	int ScorePartie(int ScoreActuel, int augmentation);							//Augmente le ScoreActuel durant la partie lorsque des pts sont fait


	//retour lorsqu'on cherche dans les fichiers sur le perso : Joueur() = ("nom", maxScore, image = "DefaultJoueur.png";
};