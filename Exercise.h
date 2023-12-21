#pragma once

class Exercise
{
	int trainId;
	TCHAR exercise[50];
	double persent;
	double maxWeight;
	int set;
	int rep;
public:
	Exercise();
	Exercise(int trainId, TCHAR exercise[50], double persent, double maxWeight, int rep, int set);
	int getTrainId();
	TCHAR* getExercise();
	double getPersent();
	int getSet();
	int getRep();
};

