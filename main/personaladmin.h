#ifndef PERSONALADMIN_H
#define PERSONALADMIN_H

#include <QString>

class PersonalAdmin
{

protected:
    QString passport;
    QString telephone;
    QString adress;

public:
    PersonalAdmin();
    ~PersonalAdmin();

    PersonalAdmin(QString, QString, QString);
    PersonalAdmin(PersonalAdmin const &);

    void setPassport(const QString &newPassport);
    QString getPassport() const;

    void setTelephone(const QString &newTelephone);
    QString getTelephone() const;

    void setAdress(const QString &newAdress);
    QString getAdress() const;

};

#endif
