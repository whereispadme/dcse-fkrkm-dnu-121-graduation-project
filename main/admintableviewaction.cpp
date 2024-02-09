#include "admintableviewaction.h"
#include "qheaderview.h"

AdminTableViewAction::AdminTableViewAction(QTableView *&tableView)
{
    this->tableView = tableView;

    this->tableModel = new QSqlTableModel(nullptr, QSqlDatabase(QSqlDatabase::database("MyDatabase")));
    this->queryModel = new QSqlQueryModel();
}

AdminTableViewAction::~AdminTableViewAction()
{
    delete tableModel;
    delete queryModel;
}

void AdminTableViewAction::setTableView()
{
    tableModel->setTable("admin");

    AdminTableViewAction::setSqlTableModelHeadersData();

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

void AdminTableViewAction::setSqlTableModelHeadersData()
{
    tableModel->setHeaderData(0, Qt::Horizontal, ("admin_id"));
    tableModel->setHeaderData(1, Qt::Horizontal, ("Логін"));
    tableModel->setHeaderData(2, Qt::Horizontal, ("Пароль"));
    tableModel->setHeaderData(3, Qt::Horizontal, ("Прізвище"));
    tableModel->setHeaderData(4, Qt::Horizontal, ("Ім'я"));
    tableModel->setHeaderData(5, Qt::Horizontal, ("По батькові"));
    tableModel->setHeaderData(6, Qt::Horizontal, ("Роль"));
}

void AdminTableViewAction::setSqlQueryModelHeadersData()
{
    queryModel->setHeaderData(0, Qt::Horizontal, ("admin_id"));
    queryModel->setHeaderData(1, Qt::Horizontal, ("Логін"));
    queryModel->setHeaderData(2, Qt::Horizontal, ("Пароль"));
    queryModel->setHeaderData(3, Qt::Horizontal, ("Прізвище"));
    queryModel->setHeaderData(4, Qt::Horizontal, ("Ім'я"));
    queryModel->setHeaderData(5, Qt::Horizontal, ("По батькові"));
    queryModel->setHeaderData(6, Qt::Horizontal, ("Роль"));

    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSortingEnabled(true);

    tableView->selectRow(0);
}

void AdminTableViewAction::generalSearchRecordsWithoutRole(QString input)
{
    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("select * from admin where ("
                  "admin_login = :login or "
                  "admin_lastname = :lastname or "
                  "admin_firstname = :firstname or "
                  "admin_middlename = :middlename);");

    query.bindValue(":login", input);
    query.bindValue(":lastname", input);
    query.bindValue(":firstname", input);
    query.bindValue(":middlename", input);

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    queryModel->setQuery(query);
    tableView->setModel(queryModel);
    AdminTableViewAction::setSqlQueryModelHeadersData();
}

void AdminTableViewAction::generalSearchRecordsWithRole(QString input, QString role)
{
    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("select * from admin where ("
                  "admin_login = :login or "
                  "admin_lastname = :lastname or "
                  "admin_firstname = :firstname or "
                  "admin_middlename = :middlename) and "
                  "admin_role = :role;");

    query.bindValue(":login", input);
    query.bindValue(":lastname", input);
    query.bindValue(":firstname", input);
    query.bindValue(":middlename", input);
    query.bindValue(":role", role);

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    queryModel->setQuery(query);
    tableView->setModel(queryModel);
    AdminTableViewAction::setSqlQueryModelHeadersData();
}

void AdminTableViewAction::filterSearchRecordsWithoutRole(Admin admin)
{
    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("select * from admin where ("
                  "admin_login = :login or "
                  "admin_lastname = :lastname or "
                  "admin_firstname = :firstname or "
                  "admin_middlename = :middlename);");

    query.bindValue(":login", admin.getLogin());
    query.bindValue(":lastname", admin.getInitials().lastname);
    query.bindValue(":firstname", admin.getInitials().firstname);
    query.bindValue(":middlename", admin.getInitials().middlename);

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    queryModel->setQuery(query);
    tableView->setModel(queryModel);
    AdminTableViewAction::setSqlQueryModelHeadersData();
}

void AdminTableViewAction::filterSearchRecordsWithRole(Admin admin)
{
    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("select * from admin where ("
                  "admin_login = :login or "
                  "admin_lastname = :lastname or "
                  "admin_firstname = :firstname or "
                  "admin_middlename = :middlename) and "
                  "admin_role = :role;");

    query.bindValue(":login", admin.getLogin());
    query.bindValue(":lastname", admin.getInitials().lastname);
    query.bindValue(":firstname", admin.getInitials().firstname);
    query.bindValue(":middlename", admin.getInitials().middlename);
    query.bindValue(":role", admin.getRole());

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    queryModel->setQuery(query);
    tableView->setModel(queryModel);
    AdminTableViewAction::setSqlQueryModelHeadersData();
}
