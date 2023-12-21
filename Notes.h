#pragma once

class Notes
{
protected:
	int id;
	TCHAR name[100];
public:
	Notes();
	Notes(int id, TCHAR name[100]);
	int getId();
	TCHAR* getName();
	void setName(TCHAR name[]);
};

