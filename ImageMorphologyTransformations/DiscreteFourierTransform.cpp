
#include "DiscreteFourierTransform.h"

using namespace cv;
using std::cout;
using std::endl;

void DFT_Ops() {
	
	Mat src = imread("lena.png", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cout << "Error Opening Image" << endl;
	}
	Mat padded;
	//expand input image to optimal size
	int m = getOptimalDFTSize(src.rows);
	int n = getOptimalDFTSize(src.cols);
	copyMakeBorder(src, padded, 0, m - src.rows, 0, n - src.cols, BORDER_CONSTANT, Scalar::all(0));
	Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexI;
	merge(planes, 2, complexI);

	dft(complexI, complexI);
	split(complexI, planes);
	magnitude(planes[0], planes[1], planes[0]);
	Mat magI = planes[0];
	//Switch to a logarithmic scale
	magI += Scalar::all(1);
	log(magI, magI);

	normalize(magI, magI, 0, 1, NORM_MINMAX);
	imshow("magI", magI);
	waitKey(0);
}