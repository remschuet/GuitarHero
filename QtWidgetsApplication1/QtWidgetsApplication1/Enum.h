#pragma once

enum fenetres { 
	Menu,
	Accueil,
	MeilleursScores,
	Informations,
	Parametre,
	Game,
	Admin
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
	MORTE,
	UNUSED
};

enum ComMode {
	BLUETOOTH,
	FILAIRE,
	CLAVIER
};