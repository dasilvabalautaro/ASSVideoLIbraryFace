#ifndef ASSDetectMovement_h
#define ASSDetectMovement_h
#include <opencv2/core.hpp>
#include <opencv2/core/opengl.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

class ASSDetectMovement
{
public:
	ASSDetectMovement();
	~ASSDetectMovement();
	bool SetImage(Mat image);
	bool Process();

private:
	Mat DiffImg(Mat img1, Mat img2, Mat img3);
	bool CheckDiff(Mat imgDiff);
	vector<Mat> images;
};


#endif