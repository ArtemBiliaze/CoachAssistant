#include "framework.h"
#include "TrainingM.h"

TrainingM::TrainingM(std::string fileName)
	: Repo(fileName)
{}

std::vector<Training>& TrainingM::getTrainings()
{
	return trainings;
}

void TrainingM::loadDataT()
{
	int id;
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
			Training training(id, descriptions);
			trainings.push_back(training);
		}
	}
	fin.close();
}

void TrainingM::saveDataT()
{
	std::ofstream fout;
	fout.open("Tranings.txt");
	for (int i = 0; i < trainings.size(); i++) {
		Training training = trainings[i];
		fout << trainings[i].getId() << std::endl;
		fout << trainings[i].getDescription() << std::endl;
	}
	fout.close();
}

void TrainingM::addTraining(Training& training)
{
	trainings.push_back(training);
}

void TrainingM::redactionT(int indexX, TCHAR description[])
{
	trainings[indexX].setDes(description);
}

bool TrainingM::checkT(TCHAR description[])
{
	auto iterator = std::find_if(trainings.begin(), trainings.end(),
		[description](Training& training) {
			return (lstrcmp(description, training.getDescription()) == 0);
		});
	return (iterator != trainings.end());
}

bool TrainingM::deleteT(int trainingId)
{
	auto iter = std::find_if(trainings.begin(), trainings.end(), [trainingId](Training& training) {
		return training.getId() == trainingId;
		});
	// ->
	if (iter != trainings.end()) {
		trainings.erase(iter);
		return true; 
	}
	return false;
}
