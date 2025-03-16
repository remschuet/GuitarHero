#pragma once

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
	UNKNOWN,
	ok,
	flecheDroite,
	flecheGauche
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