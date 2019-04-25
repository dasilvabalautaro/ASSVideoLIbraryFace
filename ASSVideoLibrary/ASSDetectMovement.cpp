#include "ASSDetectMovement.h"

ASSDetectMovement::ASSDetectMovement()
{
}

ASSDetectMovement::~ASSDetectMovement()
{
}

bool ASSDetectMovement::SetImage(Mat image)
{
	images.push_back(image);
	if (images.size() == 3)
	{
		return true;
	}
	return false;
}

bool ASSDetectMovement::Process()
{
	Mat i_minus;
	Mat i_m;
	Mat i_plus;

	cv::cvtColor(images[0], i_minus, cv::COLOR_RGB2GRAY);
	cv::cvtColor(images[1], i_m, cv::COLOR_RGB2GRAY);
	cv::cvtColor(images[2], i_plus, cv::COLOR_RGB2GRAY);
	cv::resize(i_minus, i_minus, cv::Size((320),
		(240)), cv::INTER_CUBIC);
	cv::resize(i_m, i_m, cv::Size((320),
		(240)), cv::INTER_CUBIC);
	cv::resize(i_plus, i_plus, cv::Size((320),
		(240)), cv::INTER_CUBIC);
	Mat dif = DiffImg(i_minus, i_m, i_plus);
	bool result = CheckDiff(dif);
	images.clear();
	return result;
}

Mat ASSDetectMovement::DiffImg(Mat img1, Mat img2, Mat img3) {
	Mat d1;
	Mat d2;
	Mat result;

	cv::absdiff(img3, img2, d1);
	cv::absdiff(img2, img1, d2);

	cv::bitwise_and(d1, d2, result);

	return result;
}

bool ASSDetectMovement::CheckDiff(Mat imgDiff) {
	int cols = imgDiff.cols;
	int rows = imgDiff.rows;
	int nbPixeles = cols * rows;

	int nb = 0;

	for (int i = 0; i < rows; i++)
	{
		const double* Mi = imgDiff.ptr<double>(i);
		for (int j = 0; j < cols; j++) {
			if (Mi[j] == 0.0)
			{
				nb++;
			}
		}

	}

	float avg = (nb * 100.0) / nbPixeles;
	if (avg >= 5)
	{
		return true;
	}
	return false;
}