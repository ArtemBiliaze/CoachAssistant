#pragma once
class Model
{
protected:
	int id;
	int date;
	TCHAR description[100];
public:
	Model();
	Model(int id, int date, TCHAR description[100]);
	int getId();
	int getDate();
	TCHAR* getDescription();
	void setDes(TCHAR description[100]);
};

