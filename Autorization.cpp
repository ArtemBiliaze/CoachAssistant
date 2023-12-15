#include "framework.h"
#include "Autorization.h"

void Autorization::loadData()
{
	int id;
	TCHAR login[100];
	TCHAR password[100];
	TCHAR email[100];
	TCHAR firstname[100]; 
	TCHAR lastname[100];
	TCHAR loginR[100];
	TCHAR passwordR1[100];
	TCHAR passwordR2[100];
	char buff[100];
	// ->
	users.clear();
	std::ifstream fin;
	fin.open("Userscode.txt");
	// ->
	while (!fin.eof()) {
		fin >> buff;
		if (strlen(buff) > 0) {
			id = atoi(buff);
			fin >> buff;
			mbstowcs_s(NULL, login, 100, buff, 100);
			fin >> buff;
			mbstowcs_s(NULL, password, 100, buff, 100);
			fin >> buff;
			mbstowcs_s(NULL, email, 100, buff, 100);
			fin >> buff;
			mbstowcs_s(NULL, firstname, 100, buff, 100);
			fin >> buff;
			mbstowcs_s(NULL, lastname, 100, buff, 100);
			fin >> buff;
			mbstowcs_s(NULL, loginR, 100, buff, 100);
			fin >> buff;
			mbstowcs_s(NULL, passwordR1, 100, buff, 100);
			fin >> buff;
			mbstowcs_s(NULL, passwordR2, 100, buff, 100);
			fin >> buff;
			// ->
			UserAuth user(id, login, password, email, firstname, lastname, loginR, passwordR1, passwordR2);
			users.push_back(user);
		}
	}
	fin.close();
}

void Autorization::saveData()
{
	std::ofstream fout;
	fout.open("Userscode.txt");
	std::for_each(users.begin(), users.end(),
		[&fout](UserAuth& a) {
			fout << a.getID() << std::endl;
			fout << a.getFirstName() << std::endl;
			fout << a.getlastName() << std::endl;
			fout << a.getLogin() << std::endl;
			fout << a.getPassword() << std::endl;
			fout << a.getEmail() << std::endl;
			fout << a.getLoginR() << std::endl;
			fout << a.getPasswordR1() << std::endl;
			fout << a.getPasswordR2() << std::endl;
		});
	fout.close();
}

bool Autorization::registry(TCHAR email[100], TCHAR firstname[100], TCHAR lastname[100], TCHAR loginR[100], TCHAR passwordR1[100], TCHAR passwordR2[100])
{
	auto iter2 = std::copy_if(users.begin(), users.end(), users.end(),
		[email, firstname, lastname, loginR, passwordR1, passwordR2](UserAuth& reg){
			return (lstrcmp(reg.getFirstName(), firstname) == 0 &&
				lstrcmp(reg.getlastName(), lastname) == 0 &&
				lstrcmp(reg.getEmail(), email) == 0 &&
				lstrcmp(reg.getLoginR(), loginR) == 0 &&
				lstrcmp(reg.getPasswordR1(), passwordR1) == 0 &&
				lstrcmp(reg.getPasswordR2(), passwordR2) == 0
				);
		});
	bool finish = (iter2 != users.end());
	if (finish == true)
	{
		lstrcpy(CfirstName, iter2->getFirstName());
		lstrcpy(ClastName, iter2->getlastName());
		lstrcpy(CEmail, iter2->getEmail());
		lstrcpy(CLoginR, iter2->getLoginR());
		lstrcpy(CPasswordR1, iter2->getPasswordR1());
		lstrcpy(CPasswordR2, iter2->getPasswordR2());
	}
	return finish;
}

TCHAR* Autorization::getCopyEmail()
{
	return CEmail;
}

TCHAR* Autorization::getCopyLoginR()
{
	return CLoginR;
}

TCHAR* Autorization::getCopyPasswordR1()
{
	return CPasswordR1;
}

TCHAR* Autorization::getCopyPasswordR2()
{
	return CPasswordR2;
}

bool Autorization::autheticate(TCHAR login[100], TCHAR password[100])
{
	auto iter = std::find_if(users.begin(), users.end(),
		[login, password](UserAuth& user) {
			return (
				lstrcmp(user.getLogin(), login) == 0 &&
				lstrcmp(user.getPassword(), password) == 0
			);
		});
	bool result = (iter != users.end());
	if (result == true) {
		lstrcpy(CfirstName, iter->getFirstName());
		lstrcpy(ClastName, iter->getlastName());
	}
	return result;
}

TCHAR* Autorization::getCopyFirstName()
{
	return CfirstName;
}

TCHAR* Autorization::getCopyLastName()
{
	return ClastName;
}
