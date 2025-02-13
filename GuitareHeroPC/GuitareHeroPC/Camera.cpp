#include <opencv2/opencv.hpp>
#include <iostream>

void capturerFrame(cv::VideoCapture& cap, cv::Mat& frame) {
    cap >> frame;
    if (frame.empty()) {
        std::cerr << "Erreur : Impossible de capturer la frame" << std::endl;
        exit(-1);
    }
    cv::flip(frame, frame, 1);
}

void enregistrerFrame(const cv::Mat& frame, const std::string& nomFichier) {
    cv::imwrite(nomFichier, frame);
}

void afficherImage(const std::string& nomFenetre, const std::string& nomFichier) {
    cv::Mat image = cv::imread(nomFichier);
    if (image.empty()) {
        std::cerr << "Erreur : Impossible de lire le fichier image" << std::endl;
        return;
    }
    cv::namedWindow(nomFenetre, cv::WINDOW_NORMAL);
    cv::imshow(nomFenetre, image);
    cv::waitKey(0);
    cv::destroyWindow(nomFenetre);
}

void fluxVideoEnDirect(cv::VideoCapture& cap) {
    cv::namedWindow("En direct", cv::WINDOW_AUTOSIZE);
    while (true) {
        cv::Mat frame;
        capturerFrame(cap, frame);
        cv::imshow("En direct", frame);
        if (cv::waitKey(30) >= 0) {
            enregistrerFrame(frame, "Icone.jpeg");
            break;
        }
    }
    cv::destroyAllWindows();
}

//int main() {
//    cv::VideoCapture cap(0);
//    if (!cap.isOpened()) {
//        std::cerr << "Erreur : Impossible d'ouvrir la caméra" << std::endl;
//        return -1;
//    }
//
//    fluxVideoEnDirect(cap);
//    cap.release();
//
//    afficherImage("Image joueur", "avatar.jpeg");
//
//    return 0;
//}



//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int main() {
//	cv::VideoCapture cap(0);	//ouvre la caméra de base
//	if (!cap.isOpened()) {
//		std::cerr << "Error: Could not open camera" << std::endl;
//		return -1;
//	}
//
//	cv::namedWindow("En direct", cv::WINDOW_AUTOSIZE);	//Crée la fenêtre pour la caméra
//
//	while (true) {
//		cv::Mat frame;	//Matrice de frame pour le live feed
//		cap >> frame;	//Capture une nouvelle frame
//
//		if (frame.empty()) {
//			std::cerr << "Error : Could not capture frame" << std::endl;
//			break;
//		}
//
//		cv::flip(frame, frame, 1);
//
//		cv::imshow("En direct", frame);	//Montre la vidéo
//
//		if (cv::waitKey(30) >= 0) {	//Sauvegarde la frame choisi (bouton) dans un fichier avec le nom suivant 
//			cv::imwrite("avatar.jpeg", frame);	//changer la ligne, car ça change le nom de la frame. En faire pour chaque Joueur
//			break;
//		}
//	}
//
//	cap.release();	//ferme la caméra
//	cv::destroyAllWindows();
//
//
//	//Montrer l'image àprès la capture
//	cv::Mat image = cv::imread("C:\Users\julia\OneDrive - USherbrooke\Génie informatique S1\Session 2\Projet\Essai caméra opencv\Essai caméra opencv\avatar.jpeg");
//	cv::namedWindow("Image joueur", cv::WINDOW_NORMAL);
//	cv::imshow("Image joueur", image);
//	cv::waitKey(0);	//Attend qu'un touche soit pressé pour fermer la fenêtre
//	cv::destroyWindow("Image joueur");
//
//	return 0;
//}