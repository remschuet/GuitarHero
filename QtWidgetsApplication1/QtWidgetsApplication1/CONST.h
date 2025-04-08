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

const QStringList CHANSON_FACILE = { "Billie Eilish - Bad Guy", "Coldplay - Hymn for the Weekend","Katy Perry - Hot N Cold", "Noisestorm - Crab Rave", "One Republic - Counting Stars" , "P!nk - So What", "Simple Plan - I'm Just a Kid", "The Offspring - Half Truism"};
const QStringList CHANSON_INTERMEDIAIRE = { "Billie Eilish - Bad Guy", "Coldplay - Hymn for the Weekend","Katy Perry - Hot N Cold", "Les Cowboys Fringants - Les etoiles filantes", "Noisestorm - Crab Rave", "One Republic - Counting Stars" , "P!nk - So What", "Simple Plan - I'm Just a Kid", "The Offspring - Half Truism", "The Offspring - You're Gonna Go Far, Kid"};
const QStringList CHANSON_DIFFICILE = { "Billie Eilish - Bad Guy", "Coldplay - Hymn for the Weekend", "Katy Perry - Hot N Cold", "Noisestorm - Crab Rave", "One Republic - Counting Stars" , "P!nk - So What", "Simple Plan - I'm Just a Kid", "The Offspring - Half Truism", "The Offspring - You're Gonna Go Far, Kid" };
const QStringList CHANSON_EXPERT = { "331Erock - Game of Thrones meets metal", "Billie Eilish - Bad Guy", "Blink 182 - All the Small Things", "Blink 182 - EDGING", "Boney M - Rasputin", "Coldplay - Hymn for the Weekend", "Electric Light Orchestra - Mr. Blue Sky ", "FamilyJules - Super Mario Bros. Theme", "Guns N' Roses - Sweet Child o' Mine", "Guns N' Roses - Welcome to the Jungle", "Henry Mancini & His Orchestra - La Panthere Rose theme", "Hozier - Too Sweet ", "Imagine Dragons - Enemy ", "Katy Perry - Hot N Cold", "Katy Perry - I Kissed a Girl", "Macklemore & Ryan Lewis - Can't Hold Us", "Muse - Compliance","Natasha Bedingfield - Unwritten", "Noisestorm - Crab Rave", "Olivia Rodrigo - good 4 u", "One Republic - Counting Stars", "P!nk - So What", "Panic! At The Disco - High Hopes", "Red Hot Chili Peppers - Snow (Hey Oh)", "Rick Astley - Never Gonna Give You Up", "Sheet Music Boss - Rush E",  "Simple Plan - I'm Just a Kid", "Tate McRae - Greedy", "Taylor Swift - I Knew You Were Trouble (Taylor's Version)", "Taylor Swift - We Are Never Ever Getting Back Together", "The Beatles - Hey Jude", "The Beatles - I Want To Hold Your Hand", "The Beatles - Let It Be", "The Lumineers - Ophelia", "The Offspring - Half Truism", "The Offspring - You're Gonna Go Far, Kid", "The Runaways - Cherry Bomb", "Theory of a Deadman - Rx (Medicate)", "Weezer - Buddy Holly", "Wheatus - Teenage Dirtbag"};

const int G_BUFFER_NOTE = 200;
const int G_BUFFER_NOTE_MOURIR = 400;

const int P_BONNE_NOTE_MIN = 6;
const int P_BONNE_NOTE_MAX = 9;
const int P_BONUS_JOYSTICK = 3;
const int P_MAUVAISE_TOUCHE = -2;
const int P_MANQUE_NOTE = 0;
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

const std::string BTN_BONUS_MUONS = "Muons";	//BY?


/*****************/
/*     AUTRES    */
/************** **/
const int delaiAffichage = 5000; //10000 à la base
const int delaiFillaire = 10; //delai avant choix bouton.		 si plus petit que 100 -> bug

