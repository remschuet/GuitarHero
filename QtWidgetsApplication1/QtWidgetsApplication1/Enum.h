#pragma once

enum fenetres { 
	Menu,
	Accueil,
	MeilleursScores,
	Informations,
	FinPartie,
	Parametre
};


enum NotesEtats {
	AFFICHER,
	EN_ATTENTE,
};

enum CouleurBouton {
	ROUGE,
	BLEU,
	VERT,
	JAUNE,
	MAUVE,
	QUITTER,
	JOYSTICK,
	UNKNOWN
};

enum NotesAction {
	APPUYE,
	RELACHE,
	INITIALE,
	MORTE
};

enum ComMode {
	BLUETOOTH,
	FILAIRE,
	CLAVIER
};