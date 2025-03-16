#pragma once
#include <iostream>

/***************************/
/*     CONFIG GLOBALE      */
/***************************/

const std::string CHANSON_1_MP3 = "psycho.mp3";
const std::string CHANSON_2_MP3 = "Coldplay_Hymn.mp3";
const std::string CHANSON_3_MP3 = "autre.mp3";

const std::string CHANSON_1_TXT = "psycho.txt";
const std::string CHANSON_2_TXT = "Coldplay_Hymn[MediumSingle].txt";
const std::string CHANSON_3_TXT = "autre.txt";

/***************************/
/*  MESSAGE ENTRE ARDUINO  */
/***************************/

const std::string BTN_APPUYE = "Appuye";	//a?
const std::string BTN_RELACHE = "Relache";	//r?

const std::string BTN_ROUGE = "BtRouge";	//BR?
const std::string BTN_BLEU = "BtBleu";		//BB?
const std::string BTN_VERT = "BtVert";		//BV?
const std::string BTN_JAUNE = "BtJaune";	//BJ?
const std::string BTN_MAUVE = "BtMauve";	//BM?

const std::string BTN_QUITTER = "btnQuitter";	
const std::string BTN_JOYSTICK = "btJoystick";	//BY?

const std::string BAR_GRAPH = "barGraph";	//message : 10 caracteres de 0 et 1 1010101010 -> 1 sur deux barres d'allumer

/*****************/
/*     AUTRES    */
/************** **/
const int delaiAffichage = 5500; //10000 à la base
const int delaiFillaire = 150; //delai avant choix bouton.		 si plus petit que 100 -> bug
