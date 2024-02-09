#ifndef PERSONALCLIENTTABLEVIEWACTION_H
#define PERSONALCLIENTTABLEVIEWACTION_H

#include "headers.h"
#include "personalclient.h"

class PersonalClientTableViewAction
{

protected:
    QTableView *tableView;
    QSqlTableModel *tableModel;
    QSqlQueryModel *queryModel;

public:
    PersonalClientTableViewAction(QTableView *&);
    ~PersonalClientTableViewAction();

    void setTableView();
    void setSqlTableModelHeadersData();
    void setSqlQueryModelHeadersData();

    void searchRecord(QString);

};

#endif
