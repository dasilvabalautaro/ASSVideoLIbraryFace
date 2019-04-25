#include "ASSDataML.h"


ASSDataML::ASSDataML()
{
}

ASSDataML::~ASSDataML()
{
}

void ASSDataML::setTime(int time) {
	_time = time;
}

void ASSDataML::setImages(int images) {
	_images = images;
}

void ASSDataML::setDay(int day) {
	_day = day;
}

void ASSDataML::setLog(string log) {
	_log = log;
}

void ASSDataML::setDate(string date) {
	_date = date;
}

void ASSDataML::writeLog(string fileDataML) {
	ofstream file_obj;
	file_obj.open(fileDataML, ios::app);
	file_obj << (char *)&_date << ", " << (char *)&_log << endl;
	file_obj.close();
}




void ASSDataML::writeData(string fileDataML) {
	ofstream file_obj;
	file_obj.open(fileDataML, ios::app);
	file_obj << _time << "," << _images << endl;
	file_obj.close();
}

