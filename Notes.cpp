#include "framework.h"
#include "Notes.h"

Notes::Notes() : id(0)
{
	lstrcpy(this->name, L"");
}

Notes::Notes(int id, TCHAR name[100]) : id(id)
{
	lstrcpy(this->name, name);
}

int Notes::getId()
{
	return id;
}

TCHAR* Notes::getName()
{
	return name;
}

void Notes::setName(TCHAR name[])
{
	lstrcpy(this->name, name);
}