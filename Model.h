#pragma once

class Model
{
protected:
	int id;
	TCHAR description[100];
public:
	Model();
	Model(int id, TCHAR description[100]);
	int getId();
	TCHAR* getDescription();
	void setDes(TCHAR description[100]);
};

