#pragma once
#include "Exercise.h"

class ExerciseRepo
{
	std::vector<Exercise> exercises;
	std::string filePath;
public:
	ExerciseRepo(std::string filePath);
	void loadProgram();
	void saveProgram(double pm1);
	std::vector<Exercise>& getExercice();
};

