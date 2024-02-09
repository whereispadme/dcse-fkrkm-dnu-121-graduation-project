#include "subscriptionclienttableviewaction.h"
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

SubscriptionClientTableViewAction::SubscriptionClientTableViewAction(QTableView *&tableView)
{
    this->tableView = tableView;

    this->tableModel = new QSqlTableModel(nullptr, QSqlDatabase(QSqlDatabase::database("MyDatabase")));
    this->queryModel = new QSqlQueryModel();
}

SubscriptionClientTableViewAction::~SubscriptionClientTableViewAction()
{
    delete tableModel;
    delete queryModel;
}

void SubscriptionClientTableViewAction::setTableView()
{
    tableModel->setTable("subscriptionclient");

    SubscriptionClientTableViewAction::setSqlTableModelHeadersData();

    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSortingEnabled(true);

    tableModel->setSort(1, Qt::AscendingOrder);
    tableModel->select();

    tableView->setModel(tableModel);
    tableView->selectRow(0);

    //tableView->setColumnHidden(0, true);
    tableView->verticalHeader()->setVisible(false);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    tableView->setItemDelegateForColumn(3, new CustomItemDelegate());
    tableView->setItemDelegateForColumn(4, new CustomItemDelegate());
    tableView->setItemDelegateForColumn(5, new CustomItemDelegate());
    tableView->setModel(tableModel);
}

void SubscriptionClientTableViewAction::setSqlTableModelHeadersData()
{
    tableModel->setHeaderData(0, Qt::Horizontal, ("Клієнт"));
    tableModel->setHeaderData(1, Qt::Horizontal, ("Адміністратор"));
    tableModel->setHeaderData(2, Qt::Horizontal, ("Абонемент"));
    tableModel->setHeaderData(3, Qt::Horizontal, ("Початок строку дії"));
    tableModel->setHeaderData(4, Qt::Horizontal, ("Кінець строку дії"));
    tableModel->setHeaderData(5, Qt::Horizontal, ("Тренувань залишилось"));
}

void SubscriptionClientTableViewAction::setSqlQueryModelHeadersData()
{
    queryModel->setHeaderData(0, Qt::Horizontal, ("Клієнт"));
    queryModel->setHeaderData(1, Qt::Horizontal, ("Адміністратор"));
    queryModel->setHeaderData(2, Qt::Horizontal, ("Абонемент"));
    queryModel->setHeaderData(3, Qt::Horizontal, ("Початок строку дії"));
    queryModel->setHeaderData(4, Qt::Horizontal, ("Кінець строку дії"));
    queryModel->setHeaderData(5, Qt::Horizontal, ("Тренувань залишилось"));

    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSortingEnabled(true);

    tableView->selectRow(0);
}

void SubscriptionClientTableViewAction::generalSearchRecord(QString input)
{
    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("SELECT sc.subscriptionclient_subscription_id, a.admin_lastname, c.client_firstname, s.subscription_title "
                  "FROM subscriptionclient sc "
                  "JOIN admin a ON sc.subscriptionclient_admin_id = a.admin_id "
                  "JOIN client c ON sc.subscriptionclient_client_id = c.client_id "
                  "JOIN subscription s ON sc.subscriptionclient_subscription_id = s.subscription_id "
                  "WHERE a.admin_lastname = :lastname OR c.client_firstname = :firstname OR s.subscription_title = :title");

    query.bindValue(":lastname", input);
    query.bindValue(":firstname", input);
    query.bindValue(":title", input);

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text();
            return;
    }

    queryModel->setQuery(query);
    tableView->setModel(queryModel);
    SubscriptionClientTableViewAction::setSqlQueryModelHeadersData();
}

void SubscriptionClientTableViewAction::searchRecord(QString subscription_id)
{
    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("SELECT "
    "CONCAT(c.client_lastname, ' ', LEFT(c.client_firstname, 1), '.', LEFT(c.client_middlename, 1), '.'), "
    "CONCAT(a.admin_lastname, ' ', LEFT(a.admin_firstname, 1), '.', LEFT(a.admin_middlename, 1), '.'), "
    "s.subscription_title, "
    "sc.subscriptionclient_start, "
    "sc.subscriptionclient_end, "
    "sc.subscriptionclient_trainingleft "
    "FROM "
    "subscriptionclient sc "
    "JOIN client c ON c.client_id = sc.subscriptionclient_client_id "
    "JOIN subscription s ON s.subscription_id = sc.subscriptionclient_subscription_id "
    "JOIN admin a ON a.admin_id = sc.subscriptionclient_admin_id "
    "WHERE "
    "sc.subscriptionclient_subscription_id = :subscription_id;");
    query.bindValue(":subscription_id", subscription_id);

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    queryModel->setQuery(query);
    tableView->setModel(queryModel);
    SubscriptionClientTableViewAction::setSqlQueryModelHeadersData();
}
