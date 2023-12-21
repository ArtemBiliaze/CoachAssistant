#pragma once
#include "Repo.h"
#include "Training.h"

class TrainingM : public Repo
{
	std::vector<Training> trainings;
public:
	TrainingM(std::string fileName);
	std::vector<Training>& getTrainings();
	void loadDataT() override;
	void saveDataT() override;
	void addTraining(Training& training);
	void redactionT(int indexX, TCHAR description[]);
	bool checkT(TCHAR description[]);
	bool deleteT(int trainingId);
};

