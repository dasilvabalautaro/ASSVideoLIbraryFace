#ifndef ASSFaceEither_h
#define ASSFaceEither_h

#include <iostream>

using namespace std;

class ASSFaceEither
{
public:
	ASSFaceEither();
	~ASSFaceEither();
	void SetCode(int code);
	void SetLabel(string label);
	int GetCode();
	string GetLabel();
	void Clear();
private:
	int _code;
	string _label;
};

#endif
