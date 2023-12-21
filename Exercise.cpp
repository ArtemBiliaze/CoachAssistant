#include "framework.h"
#include "Exercise.h"

Exercise::Exercise() : trainId(0), persent(0.0), maxWeight(0.0), set(0), rep(0)
{
	lstrcpy(this->exercise, L"-");
	
}

Exercise::Exercise(int trainId, TCHAR exercise[50], double persent, double maxWeight, int rep, int set)
	: trainId(trainId), persent(persent), maxWeight(maxWeight), set(set), rep(rep)
{
	lstrcpy(this->exercise, exercise);
}

int Exercise::getTrainId()
{
	return trainId;
}

TCHAR* Exercise::getExercise()
{
	return exercise;
}

double Exercise::getPersent()
{
	return persent;
}

int Exercise::getSet()
{
	return set;
}

int Exercise::getRep()
{
	return rep;
}
