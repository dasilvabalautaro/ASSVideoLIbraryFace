#ifndef ASSInitLibRecognition_h
#define ASSInitLibRecognition_h

#include <iostream>
#include "iface.h"
#include "ASSFaceError.h"

using namespace std;

class ASSInitLibRecognition
{
public:
	ASSInitLibRecognition();
	~ASSInitLibRecognition();
	void InitLib();
	void SetParams(bool cuda);
	ASSFaceError* aSFaceError = new ASSFaceError();
private:
	
	bool InitCuda();
};

#endif