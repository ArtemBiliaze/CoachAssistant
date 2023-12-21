#include "framework.h"
#include "Model.h"

Model::Model()
{
	lstrcpy(this->description, L"");
}

Model::Model(int id, TCHAR description[100])
{
	lstrcpy(this->description, description);
}

int Model::getId()
{
	return id;
}

TCHAR* Model::getDescription()
{
	return description;
}

void Model::setDes(TCHAR description[100])
{
	lstrcpy(this->description, description);
}

