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

const QStringList CHANSON_FACILE = { "Muse - Uprising", "Chanson B", "Chanson C" };
const QStringList CHANSON_INTERMEDIAIRE = { "BillieEilishBadGuy", "Chanson E", "Chanson F" };
const QStringList CHANSON_DIFFICILE = { "Chanson G", "Chanson H", "Chanson I" };
const QStringList CHANSON_EXPERT = { "Chanson J", "Chanson K", "Chanson L" };


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
const std::string BTN_JOYSTICK = "Jstick";	//BY?

const std::string BAR_GRAPH = "bG2";	//message : 10 caracteres de 0 et 1 1010101010 -> 1 sur deux barres d'allumer

/*****************/
/*     AUTRES    */
/************** **/
const int delaiAffichage = 5500; //10000 à la base
const int delaiFillaire = 10; //delai avant choix bouton.		 si plus petit que 100 -> bug

