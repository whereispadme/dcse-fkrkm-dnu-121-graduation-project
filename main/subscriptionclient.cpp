#include "subscriptionclient.h"

SubscriptionClient::SubscriptionClient()
{
}

SubscriptionClient::SubscriptionClient(const SubscriptionClient &subscriptionClient)
{
    this->start = subscriptionClient.start;
    this->end = subscriptionClient.end;
    this->trainingleft = subscriptionClient.trainingleft;
}

SubscriptionClient::~SubscriptionClient()
{
}

QString SubscriptionClient::getStart() const
{
    return start;
}

void SubscriptionClient::setStart(const QString &newStart)
{
    start = newStart;
}

QString SubscriptionClient::getEnd() const
{
    return end;
}

void SubscriptionClient::setEnd(const QString &newEnd)
{
    end = newEnd;
}

QString SubscriptionClient::getTrainingleft() const
{
    return trainingleft;
}

void SubscriptionClient::setTrainingleft(const QString &newTrainingleft)
{
    trainingleft = newTrainingleft;
}
