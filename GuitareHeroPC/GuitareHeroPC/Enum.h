#pragma once

enum NotesEtats {
	AFFICHER,
	EN_ATTENTE,
};

enum CouleurBouton {
	ROUGE,
	VERT,
	BLEU,
	JAUNE,
	MAUVE,
	QUITTER,
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