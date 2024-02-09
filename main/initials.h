#ifndef INITIALS_H
#define INITIALS_H

#include <QString>

class Initials
{

public:
    QString lastname;
    QString firstname;
    QString middlename;

    Initials();
    Initials(QString, QString, QString);
    Initials(Initials*);
    ~Initials();

};

#endif
