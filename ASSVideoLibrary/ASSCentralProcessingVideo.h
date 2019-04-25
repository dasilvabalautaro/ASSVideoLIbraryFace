#ifndef ASSCentralProcessingVideo_h
#define ASSCentralProcessingVideo_h

#include <chrono>
#include <thread>
#include "ASSCheckHardware.h"
#include "ASSFlowTrend.h"
#include "ASSDataML.h"
#include "ASSVideoCapture.h"
#include "ASSFaceDetect.h"
#include "ASSFaceEither.h"
#include "ASSVideoConfig.h"
#include "ASSDetectMovement.h"

class ASSCentralProcessingVideo
{
public:
	ASSCentralProcessingVideo();
	~ASSCentralProcessingVideo();
	ASSCheckHardware* aSSCheckHardware = new ASSCheckHardware();
	ASSFaceDetect* aSSFaceDetect = new ASSFaceDetect();
	ASSVideoConfig* aSSVideoConfig = new ASSVideoConfig();
	void RunProcessVideo();
	string errorMessage;
	Mat matImage;
	Rx::subject<char*> templateImage;
	Rx::observable<char*> observableTemplate = templateImage.get_observable();
	Rx::subject<Mat> frame;
	Rx::observable<Mat> observableFrame = frame.get_observable();
private:
	Rx::subscriber<char*> templateOut = templateImage.get_subscriber();
	Rx::subscriber<Mat> frameOut = frame.get_subscriber();
	void ObserverError();
	void ObserverTemplate();
	void InitParamsDetect();
	ASSFlowTrend* aSSFlowTrend = new ASSFlowTrend();
	ASSDetectMovement* aSSDetectMovement = new ASSDetectMovement();
	void SaveDataTraining(int day, int time, int quantity);
	ASSDataML* aSSDataML = new ASSDataML();
	ASSVideoCapture* aSSVideoCapture = new ASSVideoCapture(aSSVideoConfig);
	int SetStateFlow(int day, int minute);
	double timeDurationSingle = 0;
	void RefreshData();
	std::chrono::steady_clock::time_point startCountFacesDetected = std::chrono::steady_clock::now();
	int countImagesDetected = 0;
	int optionProcess = 1;
	void SingleDetection(Mat image);
	void BatchDetection(Mat image);
	void DetectFaces(Mat image);
	bool flagNextFrame = false;
	void GetImage(Mat image);
	
};




#endif