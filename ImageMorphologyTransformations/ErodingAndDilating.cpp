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
void Dilation(int val, void* src);
void ErosionAndDilation() {
	Mat src = imread("lena.png", IMREAD_COLOR);
	//threshold(src, src, 170, 255, THRESH_BINARY);
	vector<void*> user_type;
	user_type.push_back((Mat*)&src);
	user_type.push_back((int*)&EROSION_TYPE);
	vector<void*> user_size;
	user_size.push_back((Mat*)&src);
	user_size.push_back((int*)&EROSION_SIZE);
	namedWindow("Erosion", WINDOW_GUI_EXPANDED);
	namedWindow("Dilation", WINDOW_GUI_EXPANDED);
	//moveWindow("win2", src.cols, 0);
	createTrackbar("Type", "Erosion", NULL, 2, Erosion, (void*)&user_type);
	createTrackbar("Size", "Erosion", NULL, 20, Erosion, (void*)&user_size);
	createTrackbar("Type", "Dilation", NULL, 2, Dilation, (void*)&user_type);
	createTrackbar("Size", "Dilation", NULL, 20, Dilation, (void*)&user_size);
	Erosion(0, (void*)&user_type);
	Dilation(0, (void*)&user_type);
	waitKey(0);
}
void Dilation(int val, void* src) {
	static int dilation_type = MORPH_RECT;
	static int dilation_size = 0;
	vector<void*> user_data = *(vector<void*>*)src;

	Mat img = *(Mat*)user_data[0];
	Mat dst;
	int p = *(int*)user_data[1];
	if (p == EROSION_TYPE) {
		if (val == 0) {
			dilation_type = MORPH_RECT;
		}
		else if (val == 1) {
			dilation_type = MORPH_CROSS;
		}
		else {
			dilation_type = MORPH_ELLIPSE;
		}
	}
	else if (p == EROSION_SIZE) {
		dilation_size = val;
	}
	//Returns a structuring element of the specified sizeand shape for morphological operations.
	Mat element = getStructuringElement(dilation_type,
		Size(2 * dilation_size + 1, 2 * dilation_size + 1),
		Point(dilation_size, dilation_size));
	dilate(img, dst, element);
	imshow("Dilation", dst);

}
void Erosion(int val,void* src) {
	static int erosion_type = MORPH_RECT;
	static int erosion_size = 0;
	vector<void*> user_data = *(vector<void*>*)src ;

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
	imshow("Erosion",dst);

}