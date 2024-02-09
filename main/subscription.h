#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include "headers.h"

class Subscription
{

protected:
    QString title;
    QString type;
    QString start;
    QString end;
    QString trainingAmount;
    QString days;
    QString price;

public:
    Subscription();
    Subscription(QString, QString, QString, QString, QString, QString, QString);
    Subscription(Subscription const &);
    ~Subscription();

    QString getTitle() const;
    void setTitle(const QString &newTitle);

    QString getType() const;
    void setType(const QString &newType);

    QString getTrainingAmount() const;
    void setTrainingAmount(const QString &newTrainingAmount);

    QString getDays() const;
    void setDays(const QString &newDays);

    QString getPrice() const;
    void setPrice(const QString &newPrice);

    QString getStart() const;
    void setStart(const QString &newStart);
    QString getEnd() const;
    void setEnd(const QString &newEnd);
};

#endif
