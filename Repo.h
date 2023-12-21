#pragma once

class Repo
{
protected:
	std::string fileName;
public:
	Repo(std::string fileName);
	virtual void loadDataT() = 0;
	virtual void saveDataT() = 0;
};

