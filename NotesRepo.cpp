#include "framework.h"
#include "NotesRepo.h"

NotesRepo::NotesRepo(std::string fileName) : fileName(fileName)
{
}

void NotesRepo::loadData()
{
	// 1
	int id;
	TCHAR name[100];
	char buff[100];

	// 2
	notes.clear();
	std::ifstream fin;
	fin.open(fileName);

	// 3
	while (!fin.eof()) {
		fin.getline(buff, 100);
		if (strlen(buff) > 0) {
			id = atoi(buff);
			// ->
			fin.getline(buff, 100);
			mbstowcs_s(NULL, name, 100, buff, 100);
			// ->
			Notes note(id, name);
			notes.push_back(note);
		}
	}

	// 4
	fin.close();
}

void NotesRepo::saveData()
{
	// 1
	char buff[100];
	std::ofstream fout;
	fout.open(fileName);

	// 2
	for (auto& note : notes) {
		fout << note.getId() << std::endl;
		wcstombs_s(NULL, buff, note.getName(), 100);
		fout << buff << std::endl;
	}

	// 3
	fout.close();
}

std::vector<Notes>& NotesRepo::getNotes()
{
	return notes;
}

void NotesRepo::addNotes(Notes& note)
{
	notes.push_back(note);
}
