#pragma once
#include "Model.h"

class Training : public Model
{
public:
	Training();
	Training(int id, int date,TCHAR description[100]);
	int id;
};
