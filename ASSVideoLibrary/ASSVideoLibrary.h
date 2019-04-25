#pragma once

#ifdef ASSVIDEOLIBRARY_EXPORTS
#define ASSVIDEOLIBRARY_API __declspec(dllexport)
#else
#define ASSVIDEOLIBRARY_API __declspec(dllimport)
#endif

#include "ASSCuda.h"
#include "ASSInitLibRecognition.h"
#include "ASSCentralProcessingVideo.h"

class ASSVIDEOLIBRARY_API ASSVideoLibrary
{
public:
	 ASSVideoLibrary();
	~ ASSVideoLibrary();
	
	ASSCentralProcessingVideo* aSSCentralProcessingVideo = new ASSCentralProcessingVideo();
	void SetFileconfigurationDetect(string fileName);
	void SetConfigurationVideo(string fileName);
	void RunProcessVideo();
private:
	ASSCuda* aSSCuda = new ASSCuda();
	ASSInitLibRecognition* aSSInitLibRecognition = new ASSInitLibRecognition();
};

//extern "C" ASSVIDEOLIBRARY_API ASSVideoLibrary* createVideo();
//extern "C" ASSVIDEOLIBRARY_API void disposeVideo();


