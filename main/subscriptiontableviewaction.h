#ifndef SUBSCRIPTIONTABLEVIEWACTION_H
#define SUBSCRIPTIONTABLEVIEWACTION_H

#include "subscription.h"
#include "headers.h"

class SubscriptionTableViewAction
{

protected:
    QTableView *tableView;
    QSqlTableModel *tableModel;
    QSqlQueryModel *queryModel;

public:
    SubscriptionTableViewAction(QTableView *&);
    ~SubscriptionTableViewAction();

    void setTableView();
    void setSqlTableModelHeadersData();
    void setSqlQueryModelHeadersData();

    void generalSearchRecordsWithoutType(QString);
    void generalSearchRecordsWithType(QString, QString);
    void filterSearchRecordsWithoutType(Subscription);
    void filterSearchRecordsWithType(Subscription);

};

#endif
