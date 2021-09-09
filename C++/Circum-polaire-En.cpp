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
	int num_pic = 48 + iteration;				// My pictures start at 48 that's why there is 48+iteration
	string type_file = ".JPG";					// but this might diff for your photos
	string name = "DSC_00";
	name = name + to_string(num_pic) + type_file;
	string path = "C:/Users/Nicolas/Documents/Github_Project/StarTrail/Image/" + name;
	return (path);
}

string name_output(int num_pic, int threshold_)
{
	string type_file = ".jpg";
	string name = "DSC_00";
	name = name + to_string(num_pic) + "_" + to_string(threshold_) + type_file;
	string path = "C:/Users/Nicolas/Documents/Github_Project/StarTrail/Image/" + name;
	return path;
}

bool check_img(Mat img_check,string path)
{
	if (img_check.empty())	// Checking if the picture exist
	{					// If the picture doesn't exist then we stop the process and we inform the user of the failure
		cout << "Could not open or find the image : " << endl;
		cout << path << endl;
		system("pause");
		return false;
	}
	else
	{
		return true;
	}
}

bool compare_pixel(Mat ref_pixel_mat, Mat nn_ref_pixel_mat, int threshold_val, int layer_rgb)
{
	auto pixel_nn_ref = nn_ref_pixel_mat.at<array<uint8_t, 3>>();
	auto pixel_ref = ref_pixel_mat.at<array<uint8_t, 3>>();
	bool state = int(pixel_nn_ref[layer_rgb]) > int(pixel_ref[layer_rgb]) + threshold_val;
	return state;
}

//Star trail main program
int main() {

	time_t start, end;
	time(&start);
	Mat image_ref = imread(name_picture(0));
	bool verif = check_img(image_ref, name_picture(0));

	if (verif == false)
	{
		return -1;
	}
	int number_stack = 2;
	// read the reference picture. This picture will be the one that serves as a base for following pictures
	int threshold_value = 26;
	for (int nb = 1; nb < number_stack; nb++)	// Here 25 is the number of picture that I'm stacking. This might be 
		//a different number for your startrail
	{
		Mat image = imread(name_picture(nb));
		
		verif = check_img(image,name_picture(nb));
		if (verif == false)
		{
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

					bool status = compare_pixel(pixel_3_layer_ref, pixel_3_layer, threshold_value, layer);
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

	time(&end);
	unsigned long secondes = (unsigned long)difftime(end, start);
	imwrite(name_output(1, threshold_value), image_ref);
	// Enregistrement de la photo
	cout << "The program took " << setprecision(2) << difftime(end, start) / 60 << " minutes to complete." << endl;	//Display the time in minutes
	system("pause");
	return 0;
}
