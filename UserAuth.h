#pragma once

class UserAuth
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
public:
	UserAuth();
	UserAuth(int id, TCHAR login[100], TCHAR password[100],
		TCHAR email[100], TCHAR firstname[100],
		TCHAR lastname[100], TCHAR loginR[100], TCHAR passwordR1[100],
		TCHAR passwordR2[100]);
	int getID();
	TCHAR* getLogin();
	TCHAR* getPassword();
	TCHAR* getEmail();
	TCHAR* getFirstName();
	TCHAR* getlastName();
	TCHAR* getLoginR();
	TCHAR* getPasswordR1();
	TCHAR* getPasswordR2();
};

