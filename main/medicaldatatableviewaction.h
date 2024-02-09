#ifndef MEDICALDATATABLEVIEWACTION_H
#define MEDICALDATATABLEVIEWACTION_H

#include "medicaldata.h"
#include "headers.h"

class MedicalDataTableViewAction
{

protected:
    QTableView *tableView;
    QSqlTableModel *tableModel;
    QSqlQueryModel *queryModel;

public:
    MedicalDataTableViewAction(QTableView *&);
    ~MedicalDataTableViewAction();

    void setTableView();
    void setSqlTableModelHeadersData();
    void setSqlQueryModelHeadersData();

    void searchRecord(QString);

};

#endif
