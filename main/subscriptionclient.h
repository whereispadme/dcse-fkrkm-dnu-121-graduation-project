#ifndef SUBSCRIPTIONCLIENT_H
#define SUBSCRIPTIONCLIENT_H

#include "headers.h"

class SubscriptionClient
{

protected:
    QString start;
    QString end;
    QString trainingleft;

public:
    SubscriptionClient();
    SubscriptionClient(SubscriptionClient const &);
    ~SubscriptionClient();

    QString getStart() const;
    void setStart(const QString &newStart);

    QString getEnd() const;
    void setEnd(const QString &newEnd);

    QString getTrainingleft() const;
    void setTrainingleft(const QString &newTrainingleft);
};

#endif
