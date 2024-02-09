#include "personalclienttableviewaction.h"
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

PersonalClientTableViewAction::PersonalClientTableViewAction(QTableView *&tableView)
{
    this->tableView = tableView;

    this->tableModel = new QSqlTableModel(nullptr, QSqlDatabase(QSqlDatabase::database("MyDatabase")));
    this->queryModel = new QSqlQueryModel();
}

PersonalClientTableViewAction::~PersonalClientTableViewAction()
{
    delete tableModel;
    delete queryModel;
}

void PersonalClientTableViewAction::setTableView()
{
    tableModel->setTable("personalclient");

    PersonalClientTableViewAction::setSqlTableModelHeadersData();

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

    tableView->setItemDelegateForColumn(1, new CustomItemDelegate());
    tableView->setItemDelegateForColumn(2, new CustomItemDelegate());
    tableView->setItemDelegateForColumn(3, new CustomItemDelegate());

    tableView->setModel(tableModel);
}

void PersonalClientTableViewAction::setSqlTableModelHeadersData()
{
    tableModel->setHeaderData(0, Qt::Horizontal, ("personalclient_client_id"));
    tableModel->setHeaderData(1, Qt::Horizontal, ("Номер паспорта"));
    tableModel->setHeaderData(2, Qt::Horizontal, ("Номер телефона"));
    tableModel->setHeaderData(3, Qt::Horizontal, ("Дата народження"));
}

void PersonalClientTableViewAction::setSqlQueryModelHeadersData()
{
    queryModel->setHeaderData(0, Qt::Horizontal, ("personalclient_client_id"));
    queryModel->setHeaderData(1, Qt::Horizontal, ("Номер паспорта"));
    queryModel->setHeaderData(2, Qt::Horizontal, ("Номер телефона"));
    queryModel->setHeaderData(3, Qt::Horizontal, ("Дата народження"));

    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::NoSelection);
    tableView->setSortingEnabled(true);

    tableView->selectRow(0);
}

void PersonalClientTableViewAction::searchRecord(QString client_id)
{
    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("select * from personalclient where personalclient_client_id = :id;");
    query.bindValue(":id", client_id);

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    queryModel->setQuery(query);
    tableView->setModel(queryModel);
    PersonalClientTableViewAction::setSqlQueryModelHeadersData();
}
