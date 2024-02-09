#include "medicaldata.h"

MedicalData::MedicalData()
{
}

MedicalData::MedicalData(const MedicalData &medicalData)
{
    this->institution = medicalData.institution;
    this->doctor = medicalData.doctor;
    this->dateissue = medicalData.dateissue;
    this->dateexpiration = medicalData.dateexpiration;
    this->decision = medicalData.decision;
}

MedicalData::~MedicalData()
{
}

QString MedicalData::getInstitution() const
{
    return institution;
}

void MedicalData::setInstitution(const QString &newInstitution)
{
    institution = newInstitution;
}

QString MedicalData::getDoctor() const
{
    return doctor;
}

void MedicalData::setDoctor(const QString &newDoctor)
{
    doctor = newDoctor;
}

QString MedicalData::getDateissue() const
{
    return dateissue;
}

void MedicalData::setDateissue(const QString &newDateissue)
{
    dateissue = newDateissue;
}

QString MedicalData::getDateexpiration() const
{
    return dateexpiration;
}

void MedicalData::setDateexpiration(const QString &newDateexpiration)
{
    dateexpiration = newDateexpiration;
}

QString MedicalData::getDecision() const
{
    return decision;
}

void MedicalData::setDecision(const QString &newDecision)
{
    decision = newDecision;
}
