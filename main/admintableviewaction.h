#ifndef ADMINTABLEVIEWACTION_H
#define ADMINTABLEVIEWACTION_H

#include "admin.h"
#include "mymessagebox.h"

class AdminTableViewAction
{

protected:
    QTableView *tableView;
    QSqlTableModel *tableModel;
    QSqlQueryModel *queryModel;

public:
    AdminTableViewAction(QTableView *&);
    ~AdminTableViewAction();

    void setTableView();
    void setSqlTableModelHeadersData();
    void setSqlQueryModelHeadersData();

    void generalSearchRecordsWithoutRole(QString);
    void generalSearchRecordsWithRole(QString, QString);
    void filterSearchRecordsWithoutRole(Admin);
    void filterSearchRecordsWithRole(Admin);

};

#endif
