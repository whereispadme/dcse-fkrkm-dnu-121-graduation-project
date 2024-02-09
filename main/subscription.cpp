#include "subscription.h"

QString Subscription::getStart() const
{
    return start;
}

void Subscription::setStart(const QString &newStart)
{
    start = newStart;
}

QString Subscription::getEnd() const
{
    return end;
}

void Subscription::setEnd(const QString &newEnd)
{
    end = newEnd;
}

Subscription::Subscription()
{
}

Subscription::~Subscription()
{
}

Subscription::Subscription(QString title, QString type, QString start, QString end, QString trainingAmount, QString days, QString price)
{
    this->title = title;
    this->type = type;
    this->start = start;
    this->end = end;
    this->trainingAmount = trainingAmount;
    this->days = days;
    this->price = price;
}

Subscription::Subscription(const Subscription &subscription)
{
    this->title = subscription.title;
    this->type = subscription.type;
    this->start = subscription.start;
    this->end = subscription.end;
    this->trainingAmount = subscription.trainingAmount;
    this->days = subscription.days;
    this->price = subscription.price;
}

QString Subscription::getType() const
{
    return type;
}

void Subscription::setType(const QString &newType)
{
    type = newType;
}

QString Subscription::getTrainingAmount() const
{
    return trainingAmount;
}

void Subscription::setTrainingAmount(const QString &newTrainingAmount)
{
    trainingAmount = newTrainingAmount;
}

QString Subscription::getDays() const
{
    return days;
}

void Subscription::setDays(const QString &newDays)
{
    days = newDays;
}

QString Subscription::getPrice() const
{
    return price;
}

void Subscription::setPrice(const QString &newPrice)
{
    price = newPrice;
}

QString Subscription::getTitle() const
{
    return title;
}

void Subscription::setTitle(const QString &newTitle)
{
    title = newTitle;
}
