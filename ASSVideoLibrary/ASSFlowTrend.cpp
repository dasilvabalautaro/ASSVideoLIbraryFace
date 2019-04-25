#include "ASSFlowTrend.h"


ASSFlowTrend::ASSFlowTrend()
{
	ControlTime();
}

ASSFlowTrend::~ASSFlowTrend()
{
}

void ASSFlowTrend::Reload(string fileName) {
	if (Load(fileName)) {
		LoadMatrix();
		NormalEquations();
	}
}

void ASSFlowTrend::Split(const string& s, char c,
	vector<string>& v) {
	string::size_type i = 0;
	string::size_type j = s.find(c);

	while (j != string::npos) {
		v.push_back(s.substr(i, j - i));
		i = ++j;
		j = s.find(c, j);

		if (j == string::npos)
			v.push_back(s.substr(i, s.length()));
	}
}

bool ASSFlowTrend::Load(string fileName) {

	try
	{
		//dayOfDetect.clear();
		timeOfDetect.clear();
		quantityDetect.clear();

		ifstream data(fileName, std::ifstream::in);
		if (data.good()) {
			string row;
			while (data >> row) {
				if (!row.empty())
				{
					vector<string> v;
					Split(row, ',', v);
					/*stringstream geek(v[0]);
					int x = 0;
					geek >> x;
					dayOfDetect.push_back(x);*/
					stringstream geek1(v[0]);
					int w = 0;
					geek1 >> w;
					timeOfDetect.push_back(w);
					stringstream geek2(v[1]);
					int z = 0;
					geek2 >> z;
					quantityDetect.push_back(z);
				}
			}
			data.close();
			return true;
		}
		else
		{
			cout << "NOT DATA ML" << endl;
		}

	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}

	return false;
}

void ASSFlowTrend::LoadMatrix() {
	try
	{
		if (quantityDetect.size() > 0) {
			MatrixXf z(quantityDetect.size(), 2);
			VectorXf w(quantityDetect.size());
			X = z;
			y = w;
			for (int i = 0; i < quantityDetect.size(); i++) {
				X(i, 0) = 1;
				//X(i, 1) = dayOfDetect[i];
				X(i, 1) = timeOfDetect[i];
				y(i) = quantityDetect[i];
			}
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
}

void ASSFlowTrend::NormalEquations() {
	try
	{
		VectorXf t = (X.transpose() * X).ldlt().solve(X.transpose() * y);
		theta = t;

	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
}

int ASSFlowTrend::GetFlowTrendForMinute(int day, int minute) {
	std::thread(&ASSFlowTrend::ControlTime, this).detach();
	if (theta.size() != 0)
	{
		VectorXf m(2);
		m(0) = 1;
		//m(1) = day;
		m(1) = minute;
		int value = m.transpose() * theta;
		return value;
	}
	return 1000;
}

void ASSFlowTrend::ControlTime() {
	std::time_t t = std::time(nullptr);
	tm *ltm = std::localtime(&t);
	int hour = ltm->tm_hour;
	int day = ltm->tm_wday;

	if (hourNow < hour)
	{
		hourNow = hour;
		string fileName = to_string(day) + "-" + to_string(hour) + ".txt";
		Reload(fileName);
	}
}

