#ifndef CLIENTTABLEVIEWACTION_H
#define CLIENTTABLEVIEWACTION_H

#include "client.h"
#include "mymessagebox.h"

class ClientTableViewAction
{

protected:
    QTableView *tableView;
    QSqlTableModel *tableModel;
    QSqlQueryModel *queryModel;

public:
    ClientTableViewAction(QTableView *&);
    ~ClientTableViewAction();

    void setTableView();
    void setSqlTableModelHeadersData();
    void setSqlQueryModelHeadersData();

    void generalSearchRecordsWithoutGender(QString);
    void generalSearchRecordsWithGender(QString, QString);
    void filterSearchRecordsWithoutGender(Client);
    void filterSearchRecordsWithGender(Client);

};

#endif
