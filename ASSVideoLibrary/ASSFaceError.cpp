#include "ASSFaceError.h"


ASSFaceError::ASSFaceError()
{
}

ASSFaceError::~ASSFaceError()
{
}

void ASSFaceError::CheckError(int errorCode, string message, ErrorFace srrorFace) {
	aSFaceEither->Clear();
	aSFaceEither->SetCode(srrorFace);
	aSFaceEither->SetLabel(message);
	shootError.on_next(aSFaceEither);
}

void ASSFaceError::CheckError(int errorCode, ErrorFace srrorFace) {
	aSFaceEither->Clear();

	if (errorCode == IFACE_OK)
	{
		aSFaceEither->SetCode(ErrorFace::none);
		aSFaceEither->SetLabel("OK");
		shootError.on_next(aSFaceEither);
		return;
	}
	else if (errorCode == IFACE_ERR_LICENSE_INTEGRATION_GENERIC)
	{
		int hwIdLen = 1024;
		char hwId[1024];

		IFACE_GetHardwareId(hwId, &hwIdLen);
		char msg[256];
		sprintf_s(msg, "Your license is invalid or not present, \nplease contact support for license with this HwId %s\n", hwId);
		string msgError = msg;
		aSFaceEither->SetCode(srrorFace);
		aSFaceEither->SetLabel(msgError);
		shootError.on_next(aSFaceEither);
	}
	else
	{
		const int errorBufferLength = 1024;
		char errorBuffer[errorBufferLength];
		char msg[256];
		string msgError;
		int getErrorMsgErrorCode = IFACE_GetErrorMessage(errorCode,
			errorBufferLength, errorBuffer);
		if (getErrorMsgErrorCode == IFACE_OK)
		{
			sprintf_s(msg, "Error occurs! %s (code: %d)\n", errorBuffer, errorCode);
			msgError = msg;
		}
		else
		{
			sprintf_s(msg, "Error occurs! %s (code %d)\n", "Error occurred during error code to message translation", getErrorMsgErrorCode);
			msgError = msg;
		}
		aSFaceEither->SetCode(srrorFace);
		aSFaceEither->SetLabel(msgError);
		shootError.on_next(aSFaceEither);
	}
}