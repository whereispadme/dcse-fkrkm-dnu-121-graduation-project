#include "initials.h"

Initials::Initials()
{
    this->lastname = "";
    this->firstname = "";
    this->middlename = "";
}

Initials::Initials(QString lastname, QString firstname, QString middlename)
{
    this->lastname = lastname;
    this->firstname = firstname;
    this->middlename = middlename;
}

Initials::Initials(Initials *initials)
{
    this->lastname = initials->lastname;
    this->firstname = initials->firstname;
    this->middlename = initials->middlename;
}

Initials::~Initials()
{
}
