#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <highgui/highgui.hpp>
#include "DiscreteFourierTransform.h"
using namespace cv;
using std::cout;
using std::endl;

void ExactHorizontalAndVerticalLines() {
	Mat src = imread("stave.png", IMREAD_GRAYSCALE);
	Mat horizonMat = src.clone();
	Mat verticalMat = src.clone();
	adaptiveThreshold(~src, src, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, 0);
	int horizontalSize = src.cols / 30;
	Mat horizontalElement = getStructuringElement(MORPH_RECT, Size(horizontalSize,1));
	erode(src, horizonMat, horizontalElement);
	dilate(horizonMat, horizonMat, horizontalElement);
	
	int verticalSize = src.rows / 20;
	Mat verticalElement = getStructuringElement(MORPH_RECT, Size(1, verticalSize));
	erode(src, verticalMat, verticalElement);
	dilate(verticalMat, verticalMat, verticalElement);
	
	Mat edges; // as a mask for image egdes ; the non-zero element indicates which elements in the source should be copied
	Mat kernel = Mat::ones(5, 5, CV_8UC1);
	dilate(src, edges, kernel);
	adaptiveThreshold(edges, edges, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, 0);
	imshow("edges", edges);
	Mat smooth;
	verticalMat.copyTo(smooth);
	blur(smooth, smooth, Size(2, 2)); // smooth the edges
	verticalMat.copyTo(smooth, edges);
	imshow("verticalMat", verticalMat);
	imshow("horizonMat", horizonMat);
	waitKey(0);
}