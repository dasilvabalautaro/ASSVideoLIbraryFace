#ifndef ASSVideoConfig_h
#define ASSVideoConfig_h

#include <iostream>
#include <map>
#include <json\json.h>
#include <fstream> 
#include <sstream> 
#include "ASSFaceError.h"

using namespace std;

class ASSVideoConfig
{
public:
	ASSVideoConfig();
	~ASSVideoConfig();
	void Path(string path);
	void User(string user);
	void Password(string password);
	void Resolution(string resolution);
	void Fps(string fps);
	void ImageTemp(string name);
	void NameWindow(string name);
	void FileConfiguration(string fileName);
	string getPath();
	string getUser();
	string getPassword();
	string getResolution();
	string getFps();
	string getJsonConfig();
	string getImageTemp();
	string getNameWindow();
	void setJsonConfig();
private:
	ASSFaceError* aSFaceError = new ASSFaceError();
	string _path;
	string _user;
	string _password;
	string _resolution;
	string _fps;
	string _imageTemp;
	string _nameWindow;
	string _fileConfiguration;
	string GetConfig(string nameFile);
	const string PATH = "path";
	const string PASSWORD = "password";
	const string USER = "user";
	const string RESOLUTION = "resolution";
	const string _FPS = "fps";
	const string IMAGETEMP = "imagetemp";
	const string NAMEWINDOW = "namewindow";
};

#endif // !ASSVideoConfig_h

