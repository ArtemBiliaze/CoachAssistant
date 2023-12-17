#pragma once

class Repo
{
protected:
	std::string fileName;
public:
	Repo(std::string fileName);
	virtual void loadData() = 0;
	virtual void saveData() = 0;
};

