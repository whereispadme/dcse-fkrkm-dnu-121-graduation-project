#include "personalclient.h"

PersonalClient::PersonalClient()
{
}

PersonalClient::~PersonalClient()
{
}

PersonalClient::PersonalClient(QString passport, QString telephone, QString birthday)
{
    this->passport = passport;
    this->telephone = telephone;
    this->birthday = birthday;
}

PersonalClient::PersonalClient(const PersonalClient &personalClient)
{
    this->passport = personalClient.passport;
    this->telephone = personalClient.telephone;
    this->birthday = personalClient.birthday;
}

void PersonalClient::setPassport(const QString &newPassport)
{
    passport = newPassport;
}

QString PersonalClient::getPassport() const
{
    return passport;
}

void PersonalClient::setTelephone(const QString &newTelephone)
{
    telephone = newTelephone;
}

QString PersonalClient::getTelephone() const
{
    return telephone;
}

void PersonalClient::setBirthday(const QString &newBirthday)
{
    birthday = newBirthday;
}

QString PersonalClient::getBirthday() const
{
    return birthday;
}
