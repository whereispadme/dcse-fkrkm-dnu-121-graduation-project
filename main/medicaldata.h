#ifndef MEDICALDATA_H
#define MEDICALDATA_H

#include "headers.h"

class MedicalData
{

protected:
    QString institution;
    QString doctor;
    QString dateissue;
    QString dateexpiration;
    QString decision;

public:
    MedicalData();
    MedicalData(MedicalData const &);
    ~MedicalData();

    QString getInstitution() const;
    void setInstitution(const QString &newInstitution);

    QString getDoctor() const;
    void setDoctor(const QString &newDoctor);

    QString getDateissue() const;
    void setDateissue(const QString &newDateissue);

    QString getDateexpiration() const;
    void setDateexpiration(const QString &newDateexpiration);

    QString getDecision() const;
    void setDecision(const QString &newDecision);

};

#endif
