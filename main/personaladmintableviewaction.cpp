#include "personaladmintableviewaction.h"
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

PersonalAdminTableViewAction::PersonalAdminTableViewAction(QTableView *&tableView)
{
    this->tableView = tableView;

    this->tableModel = new QSqlTableModel(nullptr, QSqlDatabase(QSqlDatabase::database("MyDatabase")));
    this->queryModel = new QSqlQueryModel();
}

PersonalAdminTableViewAction::~PersonalAdminTableViewAction()
{
    delete tableModel;
    delete queryModel;
}

void PersonalAdminTableViewAction::setTableView()
{
    tableModel->setTable("personaladmin");

    PersonalAdminTableViewAction::setSqlTableModelHeadersData();

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

void PersonalAdminTableViewAction::setSqlTableModelHeadersData()
{
    tableModel->setHeaderData(0, Qt::Horizontal, ("personaladmin_admin_id"));
    tableModel->setHeaderData(1, Qt::Horizontal, ("Номер паспорта"));
    tableModel->setHeaderData(2, Qt::Horizontal, ("Номер телефона"));
    tableModel->setHeaderData(3, Qt::Horizontal, ("Адреса проживання"));
}

void PersonalAdminTableViewAction::setSqlQueryModelHeadersData()
{
    queryModel->setHeaderData(0, Qt::Horizontal, ("personaladmin_admin_id"));
    queryModel->setHeaderData(1, Qt::Horizontal, ("Номер паспорта"));
    queryModel->setHeaderData(2, Qt::Horizontal, ("Номер телефона"));
    queryModel->setHeaderData(3, Qt::Horizontal, ("Адреса проживання"));

    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::NoSelection);
    tableView->setSortingEnabled(true);

    tableView->selectRow(0);
}

void PersonalAdminTableViewAction::searchRecord(QString admin_id)
{
    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("select * from personaladmin where personaladmin_admin_id = :id;");
    query.bindValue(":id", admin_id);

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    queryModel->setQuery(query);
    tableView->setModel(queryModel);
    PersonalAdminTableViewAction::setSqlQueryModelHeadersData();
}
