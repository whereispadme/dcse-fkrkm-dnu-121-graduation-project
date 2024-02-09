#include "personaladmin.h"

PersonalAdmin::PersonalAdmin()
{
}

PersonalAdmin::~PersonalAdmin()
{
}

PersonalAdmin::PersonalAdmin(QString passport, QString telephone, QString adress)
{
    this->passport = passport;
    this->telephone = telephone;
    this->adress = adress;
}

PersonalAdmin::PersonalAdmin(const PersonalAdmin &personalAdmin)
{
    this->passport = personalAdmin.passport;
    this->telephone = personalAdmin.telephone;
    this->adress = personalAdmin.adress;
}

void PersonalAdmin::setPassport(const QString &newPassport)
{
    passport = newPassport;
}

QString PersonalAdmin::getPassport() const
{
    return passport;
}

void PersonalAdmin::setTelephone(const QString &newTelephone)
{
    telephone = newTelephone;
}

QString PersonalAdmin::getTelephone() const
{
    return telephone;
}

void PersonalAdmin::setAdress(const QString &newAdress)
{
    adress = newAdress;
}

QString PersonalAdmin::getAdress() const
{
    return adress;
}
