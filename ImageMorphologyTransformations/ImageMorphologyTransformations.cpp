#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <highgui/highgui.hpp>
#include "DiscreteFourierTransform.h"


using namespace cv;
using std::cout;
using std::endl;
void ErosionAndDilation();
void HitOrMiss();
void HSVInRangeThreshold();
void AddingBorders();
void ExactHorizontalAndVerticalLines();
void MoreMorphologyOps();
int main()
{
	//DFT_Ops();
	//ErosionAndDilation();
	//HitOrMiss();
	//HSVInRangeThreshold();
	//AddingBorders();
	//ExactHorizontalAndVerticalLines();	
	MoreMorphologyOps();
	return 0;
}
