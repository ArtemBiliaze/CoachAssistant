#pragma once
#include "UserAuth.h"

class Autorization
{
	std::vector<UserAuth> users;
	TCHAR CfirstName[100];
	TCHAR ClastName[100];
	TCHAR CEmail[100];
	TCHAR CLoginR[100];
	TCHAR CPasswordR1[100];
	TCHAR CPasswordR2[100];
public:
	void loadData();
	void saveData();
	bool registry(TCHAR email[100],
		TCHAR firstname[100], TCHAR lastname[100],
		TCHAR loginR[100], TCHAR passwordR1[100], TCHAR passwordR2[100]);
	TCHAR* getCopyEmail();
	TCHAR* getCopyLoginR();
	TCHAR* getCopyPasswordR1();
	TCHAR* getCopyPasswordR2();
	bool autheticate(TCHAR login[100], TCHAR password[100]);
	TCHAR* getCopyFirstName();
	TCHAR* getCopyLastName();
};

