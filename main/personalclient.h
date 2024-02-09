#ifndef PERSONALCLIENT_H
#define PERSONALCLIENT_H

#include <QString>

class PersonalClient
{

protected:
    QString passport;
    QString telephone;
    QString birthday;

public:
    PersonalClient();
    ~PersonalClient();

    PersonalClient(QString, QString, QString);
    PersonalClient(PersonalClient const &);

    void setPassport(const QString &newPassport);
    QString getPassport() const;

    void setTelephone(const QString &newTelephone);
    QString getTelephone() const;

    void setBirthday(const QString &newAdress);
    QString getBirthday() const;

};


#endif
