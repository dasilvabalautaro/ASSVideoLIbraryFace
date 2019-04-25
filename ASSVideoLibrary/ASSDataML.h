#ifndef ASSDataML_h
#define ASSDataML_h

#include <iostream> 
#include <fstream> 
#include <stdlib.h>

using namespace std;

class ASSDataML
{
public:
	ASSDataML();
	~ASSDataML();
	void writeData(string fileDataML);
	void setTime(int time);
	void setImages(int images);
	void setDay(int day);
	void setLog(string log);
	void setDate(string date);
	void writeLog(string fileDataML);
private:
	int _time;
	int _images;
	int _day;
	string _log;
	string _date;
};


#endif
