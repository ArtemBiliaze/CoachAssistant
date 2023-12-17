#pragma once
#include "Repo.h"
#include "Training.h"

class TrainingM : public Repo
{
	std::vector<Training> trainings;
public:
	TrainingM(std::string fileName);
	std::vector<Training>& getTrainings();
	void loadData() override;
	void addTraining(const Training& training);
	void redactionT(int index, TCHAR description[]);
};

