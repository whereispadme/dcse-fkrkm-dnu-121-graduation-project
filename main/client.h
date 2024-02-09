#ifndef CLIENT_H
#define CLIENT_H

#include "initials.h"
#include "personalclient.h"
#include "medicaldata.h"

class Client
{

protected:
    Initials initials;
    QString gender;
    PersonalClient personal;
    MedicalData medicalData;

public:
    Client();
    ~Client();

    Client(Client const &);
    Client(Initials, QString, PersonalClient, MedicalData);

    void setInitials(const Initials &newInitials);
    Initials getInitials() const;

    void setGender(const QString &newGender);
    QString getGender() const;

    void setPersonal(const PersonalClient &newPersonal);
    PersonalClient getPersonal() const;

    MedicalData getMedicalData() const;
    void setMedicalData(const MedicalData &newMedicalData);

};

#endif
