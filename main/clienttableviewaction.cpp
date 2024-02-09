#include "ClientTableViewAction.h"
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

ClientTableViewAction::ClientTableViewAction(QTableView *&tableView)
{
    this->tableView = tableView;

    this->tableModel = new QSqlTableModel(nullptr, QSqlDatabase(QSqlDatabase::database("MyDatabase")));
    this->queryModel = new QSqlQueryModel();
}

ClientTableViewAction::~ClientTableViewAction()
{
    delete tableModel;
    delete queryModel;
}

void ClientTableViewAction::setTableView()
{
    tableModel->setTable("client");

    ClientTableViewAction::setSqlTableModelHeadersData();

    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSortingEnabled(true);

    tableModel->setSort(1, Qt::AscendingOrder);
    tableModel->select();

    tableView->setModel(tableModel);
    tableView->selectRow(0);

    tableView->setColumnHidden(0, true);
    tableView->verticalHeader()->setVisible(false);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void ClientTableViewAction::setSqlTableModelHeadersData()
{
    tableModel->setHeaderData(0, Qt::Horizontal, ("client_id"));
    tableModel->setHeaderData(1, Qt::Horizontal, ("Прізвище"));
    tableModel->setHeaderData(2, Qt::Horizontal, ("Ім'я"));
    tableModel->setHeaderData(3, Qt::Horizontal, ("По батькові"));
    tableModel->setHeaderData(4, Qt::Horizontal, ("Стать"));
}

void ClientTableViewAction::setSqlQueryModelHeadersData()
{
    queryModel->setHeaderData(0, Qt::Horizontal, ("client_id"));
    queryModel->setHeaderData(1, Qt::Horizontal, ("Прізвище"));
    queryModel->setHeaderData(2, Qt::Horizontal, ("Ім'я"));
    queryModel->setHeaderData(3, Qt::Horizontal, ("По батькові"));
    queryModel->setHeaderData(4, Qt::Horizontal, ("Стать"));

    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSortingEnabled(true);

    tableView->selectRow(0);
}

void ClientTableViewAction::generalSearchRecordsWithoutGender(QString input)
{
    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("select * from client where ("
                  "client_lastname = :lastname or "
                  "client_firstname = :firstname or "
                  "client_middlename = :middlename);");

    query.bindValue(":lastname", input);
    query.bindValue(":firstname", input);
    query.bindValue(":middlename", input);

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    queryModel->setQuery(query);
    tableView->setModel(queryModel);
    ClientTableViewAction::setSqlQueryModelHeadersData();
}

void ClientTableViewAction::generalSearchRecordsWithGender(QString input, QString gender)
{
    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("select * from client where ("
                  "client_lastname = :lastname or "
                  "client_firstname = :firstname or "
                  "client_middlename = :middlename) and "
                  "client_gender = :gender;");

    query.bindValue(":lastname", input);
    query.bindValue(":firstname", input);
    query.bindValue(":middlename", input);
    query.bindValue(":gender", gender);

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    queryModel->setQuery(query);
    tableView->setModel(queryModel);
    ClientTableViewAction::setSqlQueryModelHeadersData();
}

void ClientTableViewAction::filterSearchRecordsWithoutGender(Client client)
{
    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("select * from client where ("
                  "client_lastname = :lastname or "
                  "client_firstname = :firstname or "
                  "client_middlename = :middlename);");

    query.bindValue(":lastname", client.getInitials().lastname);
    query.bindValue(":firstname", client.getInitials().firstname);
    query.bindValue(":middlename", client.getInitials().middlename);

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    queryModel->setQuery(query);
    tableView->setModel(queryModel);
    ClientTableViewAction::setSqlQueryModelHeadersData();
}

void ClientTableViewAction::filterSearchRecordsWithGender(Client client)
{
    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("select * from client where ("
                  "client_lastname = :lastname or "
                  "client_firstname = :firstname or "
                  "client_middlename = :middlename) and "
                  "client_gender = :gender;");

    query.bindValue(":lastname", client.getInitials().lastname);
    query.bindValue(":firstname", client.getInitials().firstname);
    query.bindValue(":middlename", client.getInitials().middlename);
    query.bindValue(":gender", client.getGender());

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    queryModel->setQuery(query);
    tableView->setModel(queryModel);
    ClientTableViewAction::setSqlQueryModelHeadersData();
}
