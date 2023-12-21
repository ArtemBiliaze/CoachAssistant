#pragma once
#include "Notes.h"

class NotesRepo
{
	std::vector<Notes> notes;
	std::string fileName;
public:
	NotesRepo(std::string fileName);
	void loadData() ;
	void saveData() ;
	std::vector<Notes>& getNotes();
	void addNotes(Notes& note);
	//void editNotes(int index, TCHAR name[]);
	//bool compare(TCHAR name[]);
};

