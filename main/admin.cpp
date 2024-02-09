#include "admin.h"

Admin::Admin()
{
}

Admin::~Admin()
{
}

Admin::Admin(const Admin &admin)
{
    this->login = admin.login;
    this->password = admin.password;
    this->initials = admin.initials;
    this->role = admin.role;
    this->personal = admin.personal;
}

Admin::Admin(QString login, QString password, Initials initials, QString role, PersonalAdmin personal)
{
    this->login = login;
    this->password = password;
    this->initials = initials;
    this->role = role;
    this->personal = personal;
}

void Admin::setLogin(QString login)
{
    this->login = login;
}

QString Admin::getLogin()
{
    return this->login;
}

void Admin::setPassword(QString password)
{
    this->password = password;
}

QString Admin::getPassword()
{
    return this->password;
}

void Admin::setInitials(Initials initials)
{
    this->initials = initials;
}

Initials Admin::getInitials()
{
    return this->initials;
}

void Admin::setRole(QString role)
{
    this->role = role;
}

QString Admin::getRole() const
{
    return role;
}

void Admin::setPersonal(const PersonalAdmin &newPersonal)
{
    personal = newPersonal;
}

PersonalAdmin Admin::getPersonal() const
{
    return personal;
}
