#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <highgui/highgui.hpp>
#include "DiscreteFourierTransform.h"
using namespace cv;
using std::cout;
using std::endl;

//use copyMakeBorder() to set the borders (extra padding to image)
//BORDER_CONSANT or BORDER_REPLICATE
void AddingBorders() {
	Mat src = imread("lena.png", IMREAD_COLOR);
	RNG rng(1);
	int top = src.rows * 0.05;
	int bottom = top;
	int left = src.cols * 0.05;
	int right = left;
	int border_type = BORDER_CONSTANT;
	Mat dst;
	for (;;) {
		copyMakeBorder(src, dst, top, bottom, left, right, 
			border_type,
			Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255)));
		imshow("dst", dst); 
		char c = waitKey(500); // wait 500 microseconds per circulation
		if (c == 'c') {
			border_type = BORDER_CONSTANT;
		}
		else if (c == 'r') {
			border_type = BORDER_REPLICATE;
		}
		else if (c == 'q') {
			break;
		}
	}
}
