#include "framework.h"
#include "TrainingM.h"

TrainingM::TrainingM(std::string fileName)
	: Repo(fileName)
{}

std::vector<Training>& TrainingM::getTrainings()
{
	return trainings;
}

void TrainingM::loadData()
{
	int id;
	int date;
	TCHAR descriptions[100];
	char buff[100];
	// ->
	trainings.clear();
	std::ifstream fin;
	fin.open(fileName);
	// ->
	while (!fin.eof()) {
		fin.getline(buff, 100);
		if (strlen(buff) > 0) {
			id = atoi(buff);
			// ->
			fin.getline(buff, 100);
			mbstowcs_s(NULL, descriptions, 100, buff, 100);
			// ->
			Training training(id, date, descriptions);
			trainings.push_back(training);
		}
	}
	fin.close();
}

void TrainingM::addTraining(const Training& training)
{
	bool isUnique = true;
	for (const auto& exTraining : trainings) {
		if (exTraining.id == training.id);
		isUnique = false;
		break;
	}
	if (isUnique) {
		trainings.push_back(training);
	}
}

void TrainingM::redactionT(int index, TCHAR description[])
{
	trainings[index].setDes(description);
}


