#include "ASSInitLibRecognition.h"

ASSInitLibRecognition::ASSInitLibRecognition()
{
}

ASSInitLibRecognition::~ASSInitLibRecognition()
{
}

void ASSInitLibRecognition::InitLib() {
	int errorCode;

	errorCode = IFACE_Init();
	if (errorCode != IFACE_OK) {
		aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::out);
	}
	else {
		cout << "License OK" << endl;
	}

}

void ASSInitLibRecognition::SetParams(bool cuda) {
	int errorCode;
	if (!cuda || !InitCuda())
	{
		errorCode = IFACE_SetParam(IFACE_GLOBAL_PARAMETERS,
			IFACE_PARAMETER_GLOBAL_THREAD_NUM, IFACE_GLOBAL_THREAD_NUM_DEFAULT);
		if (errorCode != IFACE_OK) {
			aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::log);
		}
		else {
			cout << "Params OK" << endl;
		}
	}
	
}

bool ASSInitLibRecognition::InitCuda() {
	int errorCode;
	errorCode = IFACE_SetParam(nullptr,
		IFACE_PARAMETER_GLOBAL_GPU_ENABLED, "true");
	if (errorCode == IFACE_OK) {
		errorCode = IFACE_SetParam(nullptr,
			IFACE_PARAMETER_GLOBAL_GPU_DEVICE_ID, "0");
		if (errorCode != IFACE_OK) {
			char errorMessage[256];
			IFACE_GetErrorMessage(errorCode, 256, errorMessage);
			string str(errorMessage);
			str = "CUDA not enabled: " + str;
			aSFaceError->CheckError(errorCode, str, aSFaceError->ErrorFace::log);
			return false;
		}
		else {
			cout << "CUDA successfully enabled " << endl;
			return true;
		}
	}
	else {
		aSFaceError->CheckError(errorCode, aSFaceError->ErrorFace::log);
		return false;
	}


}