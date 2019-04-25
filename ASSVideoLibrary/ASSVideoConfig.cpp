#include "ASSVideoConfig.h"



ASSVideoConfig::ASSVideoConfig() {

}

ASSVideoConfig::~ASSVideoConfig() {

}

void ASSVideoConfig::NameWindow(string name) {
	_nameWindow = name;
}

string ASSVideoConfig::getNameWindow() {
	return _nameWindow;
}

void ASSVideoConfig::ImageTemp(string name) {
	_imageTemp = name;
}

string ASSVideoConfig::getImageTemp() {
	return _imageTemp;
}

void ASSVideoConfig::Password(string password) {
	_password = password;
}

void ASSVideoConfig::Path(string path) {
	_path = path;
}

void ASSVideoConfig::User(string user) {
	_user = user;
}

void ASSVideoConfig::Resolution(string resolution) {
	_resolution = resolution;
}

void ASSVideoConfig::Fps(string fps) {
	_fps = fps;
}

string ASSVideoConfig::getFps() {
	return _fps;
}

string ASSVideoConfig::getPassword() {
	return _password;
}

string ASSVideoConfig::getPath() {
	return _path;
}

string ASSVideoConfig::getUser() {
	return _user;
}

string ASSVideoConfig::getResolution() {
	return _resolution;
}

void ASSVideoConfig::FileConfiguration(string fileName) {
	_fileConfiguration = fileName;
}

string ASSVideoConfig::getJsonConfig() {
	Json::Value jsonMap;
	std::map<std::string, std::string> params;
	params.insert(std::pair<std::string, std::string>(PATH, _path));
	params.insert(std::pair<std::string, std::string>(PASSWORD, _password));
	params.insert(std::pair<std::string, std::string>(USER, _user));
	params.insert(std::pair<std::string, std::string>(RESOLUTION, _resolution));
	params.insert(std::pair<std::string, std::string>(_FPS, _fps));
	params.insert(std::pair<std::string, std::string>(IMAGETEMP, _imageTemp));
	params.insert(std::pair<std::string, std::string>(NAMEWINDOW, _nameWindow));
	std::map<std::string, std::string>::const_iterator it = params.begin(),
		end = params.end();
	for (; it != end; ++it) {
		jsonMap[it->first] = it->second;

	}
	Json::Value root;
	root["config"] = "video_config";
	root["params"] = jsonMap;

	Json::StyledWriter writer;
	string output = writer.write(root);
	return output;
}

void ASSVideoConfig::setJsonConfig() {
	string jsonString = GetConfig(_fileConfiguration);
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(jsonString, root);
	if (!parsingSuccessful)
	{
		cout << "Error parsing the string" << endl;
		return;
	}

	const Json::Value params = root["params"];
	for (Json::Value::const_iterator it = params.begin();
		it != params.end(); ++it) {
		//cout << it.key().asString() << ':' << it->asString() << '\n';
		if (it.key().asString() == PATH) {
			_path = it->asString();
		}
		else if (it.key().asString() == PASSWORD) {
			if (!it->asString().empty()) {
				_password = it->asString();
			}
		}
		else if (it.key().asString() == USER) {
			if (!it->asString().empty()) {
				_user = it->asString();
			}
		}
		else if (it.key().asString() == RESOLUTION) {
			if (!it->asString().empty()) {
				_resolution = it->asString();
			}
		}
		else if (it.key().asString() == _FPS) {
			if (!it->asString().empty()) {
				_fps = it->asString();
			}
		}
		else if (it.key().asString() == IMAGETEMP) {
			_imageTemp = it->asString();
		}
		else if (it.key().asString() == NAMEWINDOW) {
			_nameWindow = it->asString();
		}
	}

}

string ASSVideoConfig::GetConfig(string nameFile) {
	string config;
	ifstream inconfig;
	inconfig.open(nameFile);
	if (inconfig.good()) {
		stringstream strStream;
		strStream << inconfig.rdbuf();
		config = strStream.str();
		inconfig.close();
	}
	else {
		string msg = "File configuration not found";
		aSFaceError->CheckError(ASSFACE_ERROR_FILE, msg, aSFaceError->ErrorFace::out);

	}
	return config;
}