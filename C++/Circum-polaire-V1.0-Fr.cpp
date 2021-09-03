#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>


using namespace std;
using namespace cv;

// Fonction pour obtenir le nom de chaque photo successivement
// Ici les fichiers sont issus d'un appareil photo Nikon dont le prefixe est DSC_00
// la suite correspond au numéro de la photo

string name_picture(int iteration)
{
	int num_pic = 48 + iteration;
	string type_file = ".JPG";
	string name = "DSC_00";
	name = name + to_string(num_pic) + type_file;
	string path = "C:/Users/Nicolas/Pictures/Circum-polaire-13-08-2021/" + name;
	return (path);
}
//Programme de Circum Polaire
int main(){
	
	time_t start = time(NULL);
	Mat image_ref = imread(name_picture(0));

	for (int nb = 1; nb < 25; nb++)
	{
		Mat image = imread(name_picture(nb));

		if (image.empty())	// Vérification si l'image existe
		{					// Si l'image étudié n'existe pas le programme se termine et en informe l'utilisateur
			cout << "Could not open or find the image" << endl;
			system("pause"); 
			return -1;
		}

		int axis_1 = image.cols;		//4000 pour les photos de mon appareil donc dimension verticale
		int axis_2 = image.rows;		//6000 dimension horizontale

		// Nos données sont sous la forme de class cv::mat
		// image.col(1) donne les éléments de la colonne sur les 3 couleurs
		// De même pour image.row(1)
		// Donc si on fait image.col(1).row(1) ça nous donne les 3 couleurs pour pour le pixel de coordonné (1,1)

		for (int i = 0; i < axis_1; i++)
		{
			for (int j = 0; j < axis_2; j++)
			{
					Mat pixel_3_layer = image.col(i).row(j);			// Recup du pixel de l'image
					Mat pixel_3_layer_ref = image_ref.col(i).row(j);	// Recup du pixel de ref
					
				for (int layer = 0; layer < 3; layer++)
					{
						auto pixel_nn_ref = pixel_3_layer.at<array<uint8_t, 3>>();
						auto pixel_ref = pixel_3_layer_ref.at<array<uint8_t, 3>>();
						bool status = int(pixel_nn_ref[layer]) > int(pixel_ref[layer]) + 26;

						if (status)
						{
							image_ref.at<Vec3b>(j,i) = image.at<Vec3b>(j,i);	// On remplace le pixel de référence
							// par le pixel correspondant dans la nouvelle image
							layer = 3;
						}
					}
					
			}
		}
	}
	time_t end = time(NULL);
	unsigned long secondes = (unsigned long)difftime(end, start);
	imwrite("C:/Users/Nicolas/Pictures/Circum-polaire-13-08-2021/chat.jpg", image_ref);
	// Enregistrement de la photo
	cout << "The program took "<<secondes / 60<<" minutes to complete."<<endl;
	return 0;
}