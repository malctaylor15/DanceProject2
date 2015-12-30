#include <cmath>
#include <vector> 
#include <string> 
#include <fstream>
#include <iostream>
#include <map>
#include <iomanip>

#include "DanceMove.h"

using namespace std;

vector<DanceMove> ReadInDanceMoves(string fileName)
{
	ifstream danceMovesFile;
	danceMovesFile.open(fileName);

	danceMovesFile.ignore(100, '\n');
	string name;
	double timeLength;
	double sucessRate;

	vector<DanceMove> DanceList;
	while (danceMovesFile.good())
	{
		danceMovesFile >> name >> timeLength >> sucessRate;
		DanceMove *newMove = new DanceMove(name, timeLength, sucessRate);
		DanceList.push_back(*newMove);
	}
	danceMovesFile.close();
	return DanceList;
}

void Debug1(vector<DanceMove> DanceList)
{
	//debug 
	for (int i = 0; i < DanceList.size(); i++)
	{
		cout << "Name: " << DanceList[i].getName() << '\t';
		cout << "Time Length: " << DanceList[i].getTimeLength() << '\t';
		cout << "Sucess Rate: " << DanceList[i].getSucessRate() << '\n';
		cout << "Iteration Number " << i << endl;
	}

}

double RoutineProbabilityGenerator(vector<DanceMove> DanceList, double timeRemaining, double probability)
{
	int danceMoveIndex = rand() % DanceList.size();
	double danceMoveTime = DanceList[danceMoveIndex].getTimeLength(); 
	double danceMoveProbability = DanceList[danceMoveIndex].getSucessRate(); 
	
	double newProbability = probability*danceMoveProbability;
	double newTimeRemaining = timeRemaining - danceMoveTime; 
	// debug 
	// cout << "Dance Move is " << DanceList[danceMoveIndex].getName() << endl; 

	if (newTimeRemaining > 0)
	{
		double prob = RoutineProbabilityGenerator(DanceList, newTimeRemaining, newProbability);
		// round probability 
		return round(prob*1000)/1000; 
	}
	else
	{
		return newProbability; 
	}
}

void ResultsAndOutputs(map<double, int> PDF)
{
	ofstream outfile;
	outfile.open("PDF_9e6.txt");
	outfile << "Probability, # of occurances" << endl; 
	map<double, int>::iterator aPDFEntry = PDF.begin();
	for (aPDFEntry; aPDFEntry != PDF.end(); aPDFEntry++)
	{
		outfile << aPDFEntry->first << ", " << aPDFEntry->second << endl; 
		cout << std::setprecision(4) << fixed << aPDFEntry->first << " shows up " << aPDFEntry->second << " times" << endl;
	}

}

void main()
{
	// Read dance moves with sucess rates 
	string fileName = "DanceMovesList.txt";
	vector<DanceMove> DanceList = ReadInDanceMoves(fileName);
	//Debug1(DanceList);
	double startingTime = 20; 
	int numberOfIterations = 500000; 
	map<double, int, less<double>> PDF; 

	for (int i = 0; i < 5000; i++)
	{
		double prob = RoutineProbabilityGenerator(DanceList, startingTime, 1.0);
		//cout <<"Probability is "<< prob << endl; 
		if (PDF.count(prob) == 0) // key does not exists 
		{
			// create new entry in map 
			PDF.insert(pair<double, int>(prob, 1));
			//cout << "inserted new prob into map" << endl; 
		}
		else // key exists
		{
			//add one to container (count) 
			PDF[prob] = PDF[prob] + 1; 
			//cout << prob << " count increased to " << PDF[prob]<<endl; 
		}
	} 

	for (int i = 0; i < numberOfIterations; i++)
	{
		double prob = RoutineProbabilityGenerator(DanceList, startingTime, 1.0);
		PDF[prob] = PDF[prob] + 1;
	}

	ResultsAndOutputs(PDF); 

}