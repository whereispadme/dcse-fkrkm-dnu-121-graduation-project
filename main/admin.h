#ifndef ADMIN_H
#define ADMIN_H

#include "initials.h"
#include "personaladmin.h"

class Admin
{

protected:
    QString  login;
    QString  password;
    Initials initials;
    QString  role;
    PersonalAdmin personal;

public:
    Admin();
    ~Admin();

    Admin(Admin const &);
    Admin(QString, QString, Initials, QString, PersonalAdmin);

    void setLogin(QString);
    QString getLogin();

    void setPassword(QString);
    QString getPassword();

    void setInitials(Initials);
    Initials getInitials();

    void setRole(QString);
    QString getRole() const;

    void setPersonal(const PersonalAdmin &newPersonal);
    PersonalAdmin getPersonal() const;

};

#endif
