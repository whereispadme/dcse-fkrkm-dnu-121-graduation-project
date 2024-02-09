#ifndef SUBSCRIPTIONCLIENTTABLEVIEWACTION_H
#define SUBSCRIPTIONCLIENTTABLEVIEWACTION_H

#include "subscriptionclient.h"
#include "headers.h"

class SubscriptionClientTableViewAction
{

protected:
    QTableView *tableView;
    QSqlTableModel *tableModel;
    QSqlQueryModel *queryModel;

public:
    SubscriptionClientTableViewAction(QTableView *&);
    ~SubscriptionClientTableViewAction();

    void setTableView();
    void setSqlTableModelHeadersData();
    void setSqlQueryModelHeadersData();

    void generalSearchRecord(QString);
    void searchRecord(QString);

};

#endif
