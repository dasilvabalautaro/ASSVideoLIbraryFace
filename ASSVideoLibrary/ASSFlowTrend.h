#ifndef ASSFlowTrend_h
#define ASSFlowTrend_h

#include <fstream>
#include <iostream>
#include <vector>
#include <ostream>
#include <sstream> 
#include <thread>
#include <Eigen\Dense>
#include <ctime>

using namespace Eigen;
using namespace std;


class ASSFlowTrend
{
public:
	ASSFlowTrend();
	~ASSFlowTrend();
	void Reload(string fileName);
	int GetFlowTrendForMinute(int day, int minute);

private:

	bool Load(string fileName);
	void LoadMatrix();
	void NormalEquations();
	void ControlTime();
	int hourNow = 0;
	vector<int> quantityDetect;
	//vector<int> dayOfDetect;
	vector<int> timeOfDetect;
	void Split(const string& s, char c,
		vector<string>& v);
	MatrixXf X;
	VectorXf y;
	VectorXf theta;
};

#endif


