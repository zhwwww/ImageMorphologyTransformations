#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <highgui/highgui.hpp>
#include "DiscreteFourierTransform.h"
using namespace cv;
using std::cout;
using std::endl;

//hit-or-miss operation comprises three steps
//1.erode image A with structing element B1
//2.erode the complement of image A with structing element B2
//3.AND results from step1 and step2

void HitOrMiss() {
	Mat src = imread("lena.png", IMREAD_GRAYSCALE);
	threshold(src, src, 128, 255, THRESH_BINARY);
	//cout << format(src,Formatter::FMT_MATLAB) << endl;
	//Mat kernel = (Mat_<int>(3, 3) << 0, 1, 0, 1, -1, 1, 0, 1, 0);
	Mat kernel = (Mat_<int>({ 0,1,0,
							  1,-1,1,
							  0,1,0})).reshape(1,3);
	Mat dst;
	morphologyEx(src, dst, MORPH_HITMISS, kernel);
	kernel = (kernel + 1) * 127;
	// please be well known of the interpolatin method : INTER_NEAREST 
	resize(kernel, kernel, src.size(), 0, 0, INTER_NEAREST);
	imshow("src", src);
	imshow("dst", dst);
	imshow("kernel", kernel);
	waitKey(0);
}