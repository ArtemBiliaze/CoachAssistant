#include "framework.h"
#include "UserAuth.h"

UserAuth::UserAuth() : id(0)
{
	lstrcpy(this->login, L"");
	lstrcpy(this->password, L"");
	lstrcpy(this->email, L"");
	lstrcpy(this->firstname, L"");
	lstrcpy(this->lastname, L"");
	lstrcpy(this->loginR, L"");
	lstrcpy(this->passwordR1, L"");
	lstrcpy(this->passwordR2, L"");
}

UserAuth::UserAuth(int id, TCHAR login[100], TCHAR password[100], TCHAR email[100], TCHAR firstname[100], TCHAR lastname[100], TCHAR loginR[100], TCHAR passwordR1[100], TCHAR passwordR2[100])
	: id(id)
{
	lstrcpy(this->login, login);
	lstrcpy(this->password, password);
	lstrcpy(this->email, email);
	lstrcpy(this->firstname, firstname);
	lstrcpy(this->lastname, lastname);
	lstrcpy(this->loginR, loginR);
	lstrcpy(this->passwordR1, passwordR1);
	lstrcpy(this->passwordR2, passwordR2);
}

int UserAuth::getID()
{
	return id;
}

TCHAR* UserAuth::getLogin()
{
	return login;
}

TCHAR* UserAuth::getPassword()
{
	return password;
}

TCHAR* UserAuth::getEmail()
{
	return email;
}

TCHAR* UserAuth::getFirstName()
{
	return firstname;
}

TCHAR* UserAuth::getlastName()
{
	return lastname;
}

TCHAR* UserAuth::getLoginR()
{
	return loginR;
}

TCHAR* UserAuth::getPasswordR1()
{
	return passwordR1;
}

TCHAR* UserAuth::getPasswordR2()
{
	return passwordR2;
}
