#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <highgui/highgui.hpp>
#include "DiscreteFourierTransform.h"

//apply morphological transformations such as 
//opening,closing,morphological gradient,top hat,black hat

using namespace cv;
using std::cout;
using std::endl;
void Morphology_Operations(int val, void* dat);
void MoreMorphologyOps() {
	Mat src = imread("lena.png", IMREAD_COLOR);
	void* morph_operator[] = { (void*)&src,(void*)uchar(0) };
	void* morph_elem[] = { (void*)&src,(void*)uchar(1) };
	void* morph_size[] = { (void*)&src,(void*)uchar(2) };
	namedWindow("win1", WINDOW_AUTOSIZE); // Create window
	createTrackbar("Operator:\n 0: Opening - 1: Closing  \n 2: Gradient - 3: Top Hat \n 4: Black Hat", "win1", NULL, 4, Morphology_Operations, morph_operator);
	createTrackbar("Element:\n 0: Rect - 1: Cross - 2: Ellipse", "win1",
		NULL, 2,
		Morphology_Operations, morph_elem);
	createTrackbar("Kernel size:\n 2n +1", "win1",
		NULL, 21,
		Morphology_Operations, morph_size);
	Morphology_Operations(0, morph_operator);
	waitKey(0);

}

void Morphology_Operations(int val, void* dat)
{
	static int operation = 2;
	static int morph_elem = 0;
	static int morph_size = 0;
	void** user_data = (void**)dat;
	Mat src = *(Mat*)user_data[0];
	Mat dst;
	uchar i = (uchar)user_data[1];
	// Since MORPH_X : 2,3,4,5 and 6
	if (i == 0) {
		operation = val + 2;
	}
	else if (i == 1) {
		morph_elem = val;
	}
	else {
		morph_size = val;
	}
	Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
	morphologyEx(src, dst, operation, element);
	imshow("win1", dst);
}