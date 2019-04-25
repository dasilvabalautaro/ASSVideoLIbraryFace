// ASSVideoLibrary.cpp : Defines the exported functions for the DLL application.
//

//#include "stdafx.h"
#include "ASSVideoLibrary.h"

ASSVideoLibrary::ASSVideoLibrary()
{
	bool cuda = aSSCuda->isExistCuda();
	aSSInitLibRecognition->SetParams(cuda);
	aSSInitLibRecognition->InitLib();
}

ASSVideoLibrary::~ASSVideoLibrary()
{
}

void ASSVideoLibrary::SetFileconfigurationDetect(string fileName)
{
	
	aSSCentralProcessingVideo->aSSFaceDetect->SetFileConfiguration(fileName);
	aSSCentralProcessingVideo->aSSFaceDetect->setJsonConfig();
}

void ASSVideoLibrary::SetConfigurationVideo(string fileName)
{
	aSSCentralProcessingVideo->aSSVideoConfig->FileConfiguration(fileName);
	aSSCentralProcessingVideo->aSSVideoConfig->setJsonConfig();
}
void ASSVideoLibrary::RunProcessVideo()
{
	aSSCentralProcessingVideo->RunProcessVideo();
}