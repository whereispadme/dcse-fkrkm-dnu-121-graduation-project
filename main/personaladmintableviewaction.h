#ifndef PERSONALADMINTABLEVIEWACTION_H
#define PERSONALADMINTABLEVIEWACTION_H

#include "headers.h"
#include "personaladmin.h"

class PersonalAdminTableViewAction
{

protected:
    QTableView *tableView;
    QSqlTableModel *tableModel;
    QSqlQueryModel *queryModel;

public:
    PersonalAdminTableViewAction(QTableView *&);
    ~PersonalAdminTableViewAction();

    void setTableView();
    void setSqlTableModelHeadersData();
    void setSqlQueryModelHeadersData();

    void searchRecord(QString);

};

#endif
