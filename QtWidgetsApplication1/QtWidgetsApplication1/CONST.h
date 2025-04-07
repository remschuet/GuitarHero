#pragma once
#include <iostream>
#include <QStringList>
/***************************/
/*     CONFIG GLOBALE      */
/***************************/

const std::string CHANSON_1_MP3 = "psycho.mp3";
const std::string CHANSON_2_MP3 = "Coldplay_Hymn.mp3";
const std::string CHANSON_3_MP3 = "Blitzkrieg2022.mp3";

const std::string CHANSON_1_TXT = "psycho.txt";
const std::string CHANSON_2_TXT = "Coldplay_Hymn[EasySingle].txt";
const std::string CHANSON_3_TXT = "Blitzkrieg2022.txt";

const QStringList CHANSON_FACILE = { "Billie Eilish - Bad Guy", "Coldplay - Hymn for the Weekend", "P!nk - So What", "Simple Plan - I'm Just a Kid"};
const QStringList CHANSON_INTERMEDIAIRE = { "Billie Eilish - Bad Guy", "Coldplay - Hymn for the Weekend", "P!nk - So What", "Simple Plan - I'm Just a Kid" };
const QStringList CHANSON_DIFFICILE = { "Billie Eilish - Bad Guy", "Coldplay - Hymn for the Weekend", "P!nk - So What", "Simple Plan - I'm Just a Kid" };
const QStringList CHANSON_EXPERT = { "Billie Eilish - Bad Guy", "Boney M - Rasputin", "Coldplay - Hymn for the Weekend", "Guns N' Roses - Welcome to the Jungle", "Katy Perry - I Kissed a Girl","Natasha Bedingfield - Unwritten", "P!nk - So What","Sheet Music Boss - Rush E",  "Simple Plan - I'm Just a Kid", "Tate McRae - Greedy", "Taylor Swift - I Knew You Were Trouble (Taylor's Version)", "Taylor Swift - We Are Never Ever Getting Back Together", "The Lumineers - Ophelia", "Theory of a Deadman - Rx (Medicate)"};

const int P_BONNE_NOTE_MIN = 6;
const int P_BONNE_NOTE_MAX = 9;
const int P_BONUS_JOYSTICK = 3;
const int P_MAUVAISE_TOUCHE = -2;
const int P_MANQUE_NOTE = -1;
const double P_MULTI_POINTS_BONUS_MUONS = 2.0;
const int P_TEMPS_APPLICABLE_BONUS_MUONS = 4000;

// const string CHANSON_LIST

/***************************/
/*  MESSAGE ENTRE ARDUINO  */
/***************************/

const std::string BTN_APPUYE = "App";	//a?
const std::string BTN_RELACHE = "Rel";	//r?

const std::string BTN_ROUGE = "BtR";	//BR?
const std::string BTN_BLEU = "BtB";		//BB?
const std::string BTN_VERT = "BtV";		//BV?
const std::string BTN_JAUNE = "BtJ";	//BJ?
const std::string BTN_MAUVE = "BtM";	//BM?

const std::string BTN_QUITTER = "btnQuitter";
const std::string BTN_JOYSTICK = "Mvd";	// 

const std::string BAR_GRAPH = "bG2";	//message : 10 caracteres de 0 et 1 1010101010 -> 1 sur deux barres d'allumer

const std::string BTN_BONUS_MUONS = "A CHOISIR";	//BY?


/*****************/
/*     AUTRES    */
/************** **/
const int delaiAffichage = 5000; //10000 à la base
const int delaiFillaire = 10; //delai avant choix bouton.		 si plus petit que 100 -> bug

