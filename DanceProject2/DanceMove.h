#ifndef DanceMove_h 
#define DanceMove_h 

#include <string> 

using namespace std;


class DanceMove
{
public:
	DanceMove(string name, double timeLength, double sucessRate);
	double timeLength;
	double sucessRate;
	string name;

	double getTimeLength();
	double getSucessRate();
	string getName();
};

#endif