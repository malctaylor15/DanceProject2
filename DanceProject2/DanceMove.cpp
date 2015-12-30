#include "DanceMove.h"
#include <string> 

using namespace std;

DanceMove::DanceMove(string inputName, double inputTimeLength, double inputSucessRate)
{
	this->name = inputName;
	this->timeLength = inputTimeLength;
	this->sucessRate = inputSucessRate;
}

double DanceMove::getSucessRate()
{
	return sucessRate;
}

double DanceMove::getTimeLength()
{
	return timeLength;
}

string DanceMove::getName()
{
	return name;
}
