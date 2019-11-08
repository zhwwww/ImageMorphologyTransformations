
#include "DiscreteFourierTransform.h"

using namespace cv;
using std::cout;
using std::endl;
// rearrange the quadrants of Fourier image  so that the origin is at the image center
void RearrangeFourierImage(Mat& src) {
	src = src(Rect(0, 0, src.cols & -2, src.rows & -2));
	int cx = src.cols / 2;
	int cy = src.rows / 2;
	Mat q0(src, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	Mat q1(src, Rect(cx, 0, cx, cy));  // Top-Right
	Mat q2(src, Rect(0, cy, cx, cy));  // Bottom-Left
	Mat q3(src, Rect(cx, cy, cx, cy)); // Bottom-Right
	Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);
}

void DFT_Ops() {
	
	Mat src = imread("lena.png", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cout << "Error Opening Image" << endl;
	}
	GaussianBlur(src, src, Size(3, 3), 0);
	Mat padded;
	//expand input image to optimal size
	int m = getOptimalDFTSize(src.rows);
	int n = getOptimalDFTSize(src.cols);
	copyMakeBorder(src, padded, 0, m - src.rows, 0, n - src.cols, BORDER_CONSTANT, Scalar::all(0));
	Mat planes[] = {Mat_<float>(padded), Mat_<float>(Mat::zeros(padded.size(), CV_32F)) };
	Mat complexI;
	
	merge(planes, 2, complexI);
	dft(complexI, complexI);
	split(complexI, planes);
	Mat magI, phaseI;
	magnitude(planes[0], planes[1], magI);
	phase(planes[0], planes[1], phaseI); //phaseI's value in radian

	/*test mag and phase to rebulit image through idft*/
	//set mag = 1
	MatIterator_<float> it0, it0_end, it1, it1_end;
	for (it0 = planes[0].begin<float>(), it0_end = planes[0].end<float>(), it1 = planes[1].begin<float>(), it1_end = planes[1].end<float>();
		it0 != it0_end; it0++, it1++) {
		float amp = sqrtf((*it0) * (*it0) + (*it1) * (*it1));
		*it0 = (*it0) / amp;
		*it1 = (*it1) / amp;
		/*it0 = amp;
		*it1 = 0;*/
	}
	merge(planes, 2, complexI);
	idft(complexI, complexI);
	split(complexI, planes);
 	normalize(planes[0], planes[0], 0, 1, NORM_MINMAX);	
	imshow("planes[0]", planes[0]);
	//Switch to a logarithmic scale
	//magI += Scalar::all(1);
	//log(magI, magI);
	//phaseI += Scalar::all(1);
	//log(phaseI, phaseI);

	//RearrangeFourierImage(phaseI);
	//RearrangeFourierImage(magI);

	//normalize(magI, magI, 0, 1, NORM_MINMAX);
	//normalize(phaseI, phaseI, 0, 1, NORM_MINMAX);
	//imshow("magI", magI);
	//imshow("phaseI", phaseI);

	/*planes[0] = Mat_<float>(magI);
	planes[1] = Mat::zeros(magI.size(), CV_32F);
	merge(planes, 2, complexI);
	idft(complexI, complexI);
	imshow("idft", complexI);*/

	waitKey(0);

}