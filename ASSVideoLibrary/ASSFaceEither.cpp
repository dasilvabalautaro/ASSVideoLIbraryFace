#include "ASSFaceEither.h"

void ASSFaceEither::Clear() {
	_code = 0;
	_label = "";
}

int ASSFaceEither::GetCode() {
	return _code;
}

string ASSFaceEither::GetLabel() {
	return _label;
}

void ASSFaceEither::SetCode(int code) {
	_code = code;
}

void ASSFaceEither::SetLabel(string label) {
	_label = label;
}

ASSFaceEither::ASSFaceEither()
{
}

ASSFaceEither::~ASSFaceEither()
{
}