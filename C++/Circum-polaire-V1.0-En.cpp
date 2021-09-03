#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>


using namespace std;
using namespace cv;

// This fonction update the name of the file for each iteration
// The files used are coming from a Nikon DSLR and the name of files
// start with DSC_00 then followed by the number
// A more advanced way to get the name of the file might be implemented in
// a next version of the program

string name_picture(int iteration)
{
	int num_pic = 48 + iteration;
	string type_file = ".JPG";
	string name = "DSC_00";
	name = name + to_string(num_pic) + type_file;
	string path = "C:/Users/Nicolas/Pictures/Circum-polaire-13-08-2021/" + name;
	return (path);
}
//Star trail main program
int main() {

	time_t start = time(NULL);
	Mat image_ref = imread(name_picture(0));
	// read the reference picture. This picture will be the one that serves as a base for following pictures
	for (int nb = 1; nb < 25; nb++)	// Here 25 is the number of picture that I'm stacking. This might be 
		//a different number for your startrail
	{
		Mat image = imread(name_picture(nb));

		if (image.empty())	// Checking if the picture exist
		{					// If the picture doesn't exist then we stop the process and we inform the user of the failure
			cout << "Could not open or find the image" << endl;
			system("pause");
			return -1;
		}

		int axis_1 = image.cols;		//Vertical Resolution of the picture
		int axis_2 = image.rows;		//Horizontal

		// The data is under cv::Mat class
		// image.col(1) gives all the elements present in one column on the three RGB layers
		// image.row(1) same but with the row
		// image.col(1).row(1) give the three layers value for the pixel (1;1)

		for (int i = 0; i < axis_1; i++)
		{
			for (int j = 0; j < axis_2; j++)
			{
				Mat pixel_3_layer = image.col(i).row(j);			// Pixel from the picture compared
				Mat pixel_3_layer_ref = image_ref.col(i).row(j);	// Pixel from the reference

				for (int layer = 0; layer < 3; layer++)
				{
					auto pixel_nn_ref = pixel_3_layer.at<array<uint8_t, 3>>();
					auto pixel_ref = pixel_3_layer_ref.at<array<uint8_t, 3>>();
					bool status = int(pixel_nn_ref[layer]) > int(pixel_ref[layer]) + 26;

					if (status)										//Pixel are more than 10% different 
					{
						image_ref.at<Vec3b>(j, i) = image.at<Vec3b>(j, i);	// We erease the reference pixel and 
						// replace it with the studied pixel
						
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
	cout << "The program took " << int(secondes / 60) << " minutes to complete." << endl;	//Display the time in minutes
	return 0;
}