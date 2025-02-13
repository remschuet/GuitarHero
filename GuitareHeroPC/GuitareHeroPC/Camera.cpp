#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	cv::VideoCapture cap(0);	//ouvre la cam�ra de base
	if (!cap.isOpened()) {
		std::cerr << "Error: Could not open camera" << std::endl;
		return -1;
	}

	cv::namedWindow("En direct", cv::WINDOW_AUTOSIZE);	//Cr�e la fen�tre pour la cam�ra

	while (true) {
		cv::Mat frame;	//Matrice de frame pour le live feed
		cap >> frame;	//Capture une nouvelle frame

		if (frame.empty()) {
			std::cerr << "Error : Could not capture frame" << std::endl;
			break;
		}

		cv::flip(frame, frame, 1);

		cv::imshow("En direct", frame);	//Montre la vid�o

		if (cv::waitKey(30) >= 0) {	//Sauvegarde la frame choisi (bouton) dans un fichier avec le nom suivant 
			cv::imwrite("avatar.jpeg", frame);	//changer la ligne, car �a change le nom de la frame. En faire pour chaque Joueur
			break;
		}
	}

	cap.release();	//ferme la cam�ra
	cv::destroyAllWindows();


	//Montrer l'image �pr�s la capture
	cv::Mat image = cv::imread("C:\Users\julia\OneDrive - USherbrooke\G�nie informatique S1\Session 2\Projet\Essai cam�ra opencv\Essai cam�ra opencv\avatar.jpeg");
	cv::namedWindow("Image joueur", cv::WINDOW_NORMAL);
	cv::imshow("Image joueur", image);
	cv::waitKey(0);	//Attend qu'un touche soit press� pour fermer la fen�tre
	cv::destroyWindow("Image joueur");

	return 0;
}