#include "ASSCentralProcessingVideo.h"

ASSCentralProcessingVideo::ASSCentralProcessingVideo()
{
	aSSCheckHardware->GetSystemTimesAddress();
	InitParamsDetect();
	ObserverError();
	ObserverTemplate();
}

ASSCentralProcessingVideo::~ASSCentralProcessingVideo()
{
}

void ASSCentralProcessingVideo::ObserverError()
{
	auto faceError = aSSFaceDetect->observableError.map([](string message) {
		return message;
	});

	auto subscriptionError = faceError.subscribe([this](string message) {
		cout << message << endl;
		errorMessage = message;
	});
}

void ASSCentralProcessingVideo::SaveDataTraining(int day, int time, int quantity) {
	std::time_t t = std::time(nullptr);
	tm *ltm = std::localtime(&t);
	int hour = ltm->tm_hour;
	string fileName = to_string(day) + "-" + to_string(hour) + ".txt";
	aSSDataML->setTime(time);
	aSSDataML->setImages(quantity);
	aSSDataML->setDay(day);
	aSSDataML->writeData(fileName);
}

int ASSCentralProcessingVideo::SetStateFlow(int day, int minute) {
	int quantity = aSSFlowTrend->GetFlowTrendForMinute(day, minute - 10);
	aSSVideoCapture->resetCountBatch();
	aSSFaceDetect->resetCountBatch();
	if (timeDurationSingle != 0.0)
	{
		int imagesWait = (60 / timeDurationSingle) / 2;
		
		if (quantity > imagesWait)
		{

			return 1;
		}
		if (quantity <= imagesWait && quantity != 0)
		{
			return 2;
		}
		else
		{
			return 3;
		}

	}
	return 1;
}

void ASSCentralProcessingVideo::RefreshData() {
	std::chrono::steady_clock::time_point endCountFacesDetected = std::chrono::steady_clock::now();
	int diff = std::chrono::duration_cast<std::chrono::minutes>(endCountFacesDetected - startCountFacesDetected).count();
	if (diff >= 1)
	{
		std::time_t t = std::time(nullptr);
		tm *ltm = std::localtime(&t);
		int hour = ltm->tm_hour;
		int day = ltm->tm_wday;
		int min = (hour * 60) + ltm->tm_min;
		std::thread(&ASSCentralProcessingVideo::SaveDataTraining, this,
			day, min, countImagesDetected).detach();
		startCountFacesDetected = std::chrono::steady_clock::now();
		countImagesDetected = 0;

		optionProcess = SetStateFlow(day, min + 1);

	}
}

void ASSCentralProcessingVideo::SingleDetection(Mat image) {
	aSSVideoCapture->writeImage(image);
	aSSFaceDetect->SetFileImage(aSSVideoCapture->GetNameFileImage());
	chrono::steady_clock sc;
	auto start = sc.now();
	int count = aSSFaceDetect->ProccessDetectSingle();
	if (count != 0)
	{
		auto end = sc.now();
		auto time_span = static_cast<chrono::duration<double>>(end - start);
		timeDurationSingle = time_span.count();

	}
	countImagesDetected += count;
}

void ASSCentralProcessingVideo::BatchDetection(Mat image) {
	aSSVideoCapture->writeImageBatch(image);
	if (aSSVideoCapture->getCountBatch() % 10 == 0) {
		aSSFaceDetect->SetFileImage(aSSVideoCapture->GetNameFileImage());
		countImagesDetected += aSSFaceDetect->ProccessDetectBatch();
	}
}

void ASSCentralProcessingVideo::DetectFaces(Mat image) {

	RefreshData();

	switch (optionProcess)
	{
	case 1:
		SingleDetection(image);
		cout << "SINGLE DETECTION" << endl;
		break;
	case 2:
		BatchDetection(image);
		cout << "BATCH DETECTION" << endl;
		break;
	case 3:
		if (aSSDetectMovement->SetImage(image))
		{
			if (aSSDetectMovement->Process()) {
				optionProcess = 1;
			}
			cout << "MOVEMENT DETECTION" << endl;
		}
		break;
	default:
		break;
	}

	flagNextFrame = false;
}

void ASSCentralProcessingVideo::RunProcessVideo() {

	auto frame_input
		= aSSVideoCapture->observableImage.map([](Mat p) {
		return p;
	});

	auto subscription = frame_input.subscribe([this](Mat p) {
		cv::resize(p, p, cv::Size(), 0.5, 0.5, INTER_LINEAR_EXACT);


		if (!flagNextFrame) {
			flagNextFrame = true;

			std::thread squ(&ASSCentralProcessingVideo::DetectFaces, this, p);
			squ.detach();

		}

		aSSVideoCapture->countFrame += 1;
		
		frameOut.on_next(p);


	});
	
	aSSVideoCapture->processVideo();

	subscription.unsubscribe();

}

void ASSCentralProcessingVideo::GetImage(Mat image) {

	matImage = image;

}

void ASSCentralProcessingVideo::InitParamsDetect() {

	aSSFaceDetect->Start();

}

void ASSCentralProcessingVideo::ObserverTemplate() {

	auto template_input
		= aSSFaceDetect->observableTemplate.map([](char* m) {
		return m;
	});

	auto subscription = template_input.subscribe([this](char* m) {
		
		templateOut.on_next(m);
		
	});

}