#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <highgui/highgui.hpp>

using namespace cv;
using std::cout;
using std::endl;
using std::vector;
const int EROSION_TYPE = 1;
const int EROSION_SIZE = 2;
//how to apply two very common morphological operators:
//Erosion and Dilation
void Erosion(int val, void* src);
void ErosionAndDilation() {
	Mat src = imread("lena.png", IMREAD_GRAYSCALE);
	void* user_type[] = { (Mat*)&src,(int*)&EROSION_TYPE };
	void* user_size[] = { (Mat*)&src,(int*)&EROSION_SIZE };

	namedWindow("win1", WINDOW_GUI_NORMAL);
	createTrackbar("Type", "win1", NULL, 2, Erosion, (void*)user_type);
	createTrackbar("Size", "win1", NULL, 20, Erosion, (void*)user_size);
	Erosion(0, (void*)&user_type);
	waitKey(0);
}

void Erosion(int val,void* src) {
	static int erosion_type = MORPH_RECT;
	static int erosion_size = 1;
	void** user_data = (void**)src;
	Mat img = *(Mat*)user_data[0];
	Mat dst;
	int p = *(int*)user_data[1];
 	if (p == EROSION_TYPE) {
		if (val == 0) {
			erosion_type = MORPH_RECT;
		}
		else if (val == 1) {
			erosion_type = MORPH_CROSS;
		}
		else {
			erosion_type = MORPH_ELLIPSE;
		}
	}
	else if (p == EROSION_SIZE) {
		erosion_size = val;
	}
	//Returns a structuring element of the specified sizeand shape for morphological operations.
	Mat element = getStructuringElement(erosion_type,
		Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		Point(erosion_size, erosion_size));
	erode(img, dst, element);
	imshow("win1",dst);

}