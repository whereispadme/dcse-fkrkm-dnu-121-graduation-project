#include "client.h"

Client::Client()
{
}

Client::~Client()
{
}

Client::Client(const Client &client)
{
    this->initials = client.initials;
    this->gender = client.gender;
    this->personal = client.personal;
    this->medicalData = client.medicalData;
}

Client::Client(Initials initials, QString gender, PersonalClient personal, MedicalData medicalData)
{
    this->initials = initials;
    this->gender = gender;
    this->personal = personal;
    this->medicalData = medicalData;
}

void Client::setInitials(const Initials &newInitials)
{
    initials = newInitials;
}

Initials Client::getInitials() const
{
    return initials;
}

void Client::setGender(const QString &newGender)
{
    gender = newGender;
}

QString Client::getGender() const
{
    return gender;
}

void Client::setPersonal(const PersonalClient &newPersonal)
{
    personal = newPersonal;
}

PersonalClient Client::getPersonal() const
{
    return personal;
}

MedicalData Client::getMedicalData() const
{
    return medicalData;
}

void Client::setMedicalData(const MedicalData &newMedicalData)
{
    medicalData = newMedicalData;
}
