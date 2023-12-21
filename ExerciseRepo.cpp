#include "framework.h"
#include "ExerciseRepo.h"

ExerciseRepo::ExerciseRepo(std::string filePath) : filePath(filePath)
{
}

void ExerciseRepo::loadProgram()
{
	//1
	int trainId;
	TCHAR exercise[50];
	double persent;
	double maxWeight;
	int set;
	int rep;
	char buff[50];

	//2
	exercises.clear();
	std::ifstream fin;
	fin.open("BenchProtocol");

	//3
	while (!fin.eof()) {
		fin.getline( buff,50);
		if (strlen(buff) > 0) {
			trainId = atoi(buff);
			fin.getline(buff, 50);
			mbstowcs_s(NULL, exercise, 50, buff, 50);
			fin.getline(buff, 50);
			persent = atof(buff);
			fin.getline(buff, 50);
			maxWeight = atof(buff);
			fin.getline(buff, 50);
			set = atof(buff);
			fin.getline(buff, 50);
			rep = atof(buff);
			

			//->
			Exercise exerc(trainId, exercise,persent, maxWeight, set, rep);
			exercises.push_back(exerc);
		}
	}

	//4
	fin.close();
}


void ExerciseRepo::saveProgram(double pm1)
{
	char buff[50];
	std::ofstream fout;
	fout.open(filePath);

	for (auto& exerc : exercises) {
		fout << exerc.getTrainId() << " ";
		wcstombs_s(NULL, buff, exerc.getExercise(), 50);
		fout << buff << "  ";
		fout << exerc.getPersent() * pm1 / 100 << "êã  ";
		fout << exerc.getSet() << " * ";
		fout << exerc.getRep() << std::endl;
	}
	fout.close();
}

std::vector<Exercise>& ExerciseRepo::getExercice()
{
	return exercises;
}
