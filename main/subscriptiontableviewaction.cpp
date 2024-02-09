#include "subscriptiontableviewaction.h"
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

SubscriptionTableViewAction::SubscriptionTableViewAction(QTableView *&tableView)
{
    this->tableView = tableView;

    this->tableModel = new QSqlTableModel(nullptr, QSqlDatabase(QSqlDatabase::database("MyDatabase")));
    this->queryModel = new QSqlQueryModel();
}

SubscriptionTableViewAction::~SubscriptionTableViewAction()
{
    delete tableModel;
    delete queryModel;
}

void SubscriptionTableViewAction::setTableView()
{
    tableModel->setTable("subscription");

    SubscriptionTableViewAction::setSqlTableModelHeadersData();

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

    tableView->setItemDelegateForColumn(3, new CustomItemDelegate());
    tableView->setItemDelegateForColumn(4, new CustomItemDelegate());
    tableView->setItemDelegateForColumn(5, new CustomItemDelegate());
    tableView->setItemDelegateForColumn(6, new CustomItemDelegate());
    tableView->setItemDelegateForColumn(7, new CustomItemDelegate());
    tableView->setModel(tableModel);
}

void SubscriptionTableViewAction::setSqlTableModelHeadersData()
{
    tableModel->setHeaderData(0, Qt::Horizontal, ("subscription_id"));
    tableModel->setHeaderData(1, Qt::Horizontal, ("Назва"));
    tableModel->setHeaderData(2, Qt::Horizontal, ("Тип абонементу"));
    tableModel->setHeaderData(3, Qt::Horizontal, ("Час початку"));
    tableModel->setHeaderData(4, Qt::Horizontal, ("Час закінчення"));
    tableModel->setHeaderData(5, Qt::Horizontal, ("Дні відвідування"));
    tableModel->setHeaderData(6, Qt::Horizontal, ("Кількість тренувань"));
    tableModel->setHeaderData(7, Qt::Horizontal, ("Ціна (грн.)"));
}

void SubscriptionTableViewAction::setSqlQueryModelHeadersData()
{
    queryModel->setHeaderData(0, Qt::Horizontal, ("subscription_id"));
    queryModel->setHeaderData(1, Qt::Horizontal, ("Назва"));
    queryModel->setHeaderData(2, Qt::Horizontal, ("Тип абонементу"));
    queryModel->setHeaderData(3, Qt::Horizontal, ("Час початку"));
    queryModel->setHeaderData(4, Qt::Horizontal, ("Час закінчення"));
    queryModel->setHeaderData(5, Qt::Horizontal, ("Дні відвідування"));
    queryModel->setHeaderData(6, Qt::Horizontal, ("Кількість тренувань"));
    queryModel->setHeaderData(7, Qt::Horizontal, ("Ціна (грн.)"));

    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSortingEnabled(true);

    tableView->selectRow(0);
}

void SubscriptionTableViewAction::generalSearchRecordsWithoutType(QString input)
{
    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("select * from subscription where ("
                  "subscription_title = :title or "
                  "subscription_trainingamount = :trainingamount or "
                  "subscription_price = :price);");

    query.bindValue(":title", input);
    query.bindValue(":trainingamount", input);
    query.bindValue(":price", input);

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    queryModel->setQuery(query);
    tableView->setModel(queryModel);
    SubscriptionTableViewAction::setSqlQueryModelHeadersData();
}

void SubscriptionTableViewAction::generalSearchRecordsWithType(QString input, QString type)
{
    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("select * from subscription where ("
                  "subscription_title = :title or "
                  "subscription_trainingamount = :trainingamount or "
                  "subscription_price = :price) and "
                  "subscription_type = :type;");

    query.bindValue(":title", input);
    query.bindValue(":trainingamount", input);
    query.bindValue(":price", input);
    query.bindValue(":type", type);

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    queryModel->setQuery(query);
    tableView->setModel(queryModel);
    SubscriptionTableViewAction::setSqlQueryModelHeadersData();
}

void SubscriptionTableViewAction::filterSearchRecordsWithoutType(Subscription subscription)
{
    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("select * from subscription where ("
                  "subscription_title = :title or "
                  "subscription_trainingamount = :trainingamount or "
                  "subscription_price = :price);");

    query.bindValue(":title", subscription.getTitle());
    query.bindValue(":trainingamount", subscription.getTrainingAmount());
    query.bindValue(":price", subscription.getPrice());

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    queryModel->setQuery(query);
    tableView->setModel(queryModel);
    SubscriptionTableViewAction::setSqlQueryModelHeadersData();
}

void SubscriptionTableViewAction::filterSearchRecordsWithType(Subscription subscription)
{
    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("select * from subscription where ("
                  "subscription_title = :title or "
                  "subscription_trainingamount = :trainingamount or "
                  "subscription_price = :price) and "
                  "subscription_type = :type;");

    query.bindValue(":title", subscription.getTitle());
    query.bindValue(":trainingamount", subscription.getTrainingAmount());
    query.bindValue(":price", subscription.getPrice());
    query.bindValue(":type", subscription.getType());

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    queryModel->setQuery(query);
    tableView->setModel(queryModel);
    SubscriptionTableViewAction::setSqlQueryModelHeadersData();
}
