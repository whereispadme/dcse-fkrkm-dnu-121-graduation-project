#include "medicaldatatableviewaction.h"
#include "qheaderview.h"

class CustomItemDelegate : public QStyledItemDelegate
{
public:
    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override
    {
        QStyledItemDelegate::initStyleOption(option, index);
        option->displayAlignment = Qt::AlignCenter;
    }
};

MedicalDataTableViewAction::MedicalDataTableViewAction(QTableView *&tableView)
{
    this->tableView = tableView;

    this->tableModel = new QSqlTableModel(nullptr, QSqlDatabase(QSqlDatabase::database("MyDatabase")));
    this->queryModel = new QSqlQueryModel();
}

MedicalDataTableViewAction::~MedicalDataTableViewAction()
{
    delete tableModel;
    delete queryModel;
}

void MedicalDataTableViewAction::setTableView()
{
    tableModel->setTable("medicaldata");

    MedicalDataTableViewAction::setSqlTableModelHeadersData();

    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::NoSelection);
    tableView->setSortingEnabled(true);

    tableModel->setSort(1, Qt::AscendingOrder);
    tableModel->select();

    tableView->setModel(tableModel);
    tableView->selectRow(0);

    tableView->setColumnHidden(0, true);
    tableView->verticalHeader()->setVisible(false);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    tableView->setItemDelegateForColumn(3, new CustomItemDelegate());
    tableView->setItemDelegateForColumn(4, new CustomItemDelegate());
    tableView->setModel(tableModel);
}

void MedicalDataTableViewAction::setSqlTableModelHeadersData()
{
    tableModel->setHeaderData(0, Qt::Horizontal, ("medicaldata_сlient_id"));
    tableModel->setHeaderData(1, Qt::Horizontal, ("Заклад, що видав"));
    tableModel->setHeaderData(2, Qt::Horizontal, ("Лікар"));
    tableModel->setHeaderData(3, Qt::Horizontal, ("Початок дії"));
    tableModel->setHeaderData(4, Qt::Horizontal, ("Кінець дії"));
    tableModel->setHeaderData(5, Qt::Horizontal, ("Висновок лікаря"));
}

void MedicalDataTableViewAction::setSqlQueryModelHeadersData()
{
    queryModel->setHeaderData(0, Qt::Horizontal, ("medicaldata_сlient_id"));
    queryModel->setHeaderData(1, Qt::Horizontal, ("Заклад, що видав"));
    queryModel->setHeaderData(2, Qt::Horizontal, ("Лікар"));
    queryModel->setHeaderData(3, Qt::Horizontal, ("Початок дії"));
    queryModel->setHeaderData(4, Qt::Horizontal, ("Кінець дії"));
    queryModel->setHeaderData(5, Qt::Horizontal, ("Висновок лікаря"));

    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::NoSelection);
    tableView->setSortingEnabled(true);

    tableView->selectRow(0);
}

void MedicalDataTableViewAction::searchRecord(QString client_id)
{
    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("select * from medicaldata where medicaldata_сlient_id = :id;");
    query.bindValue(":id", client_id);

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    queryModel->setQuery(query);
    tableView->setModel(queryModel);
    MedicalDataTableViewAction::setSqlQueryModelHeadersData();
}
