#include "reportwindow.h"
#include "ui_reportwindow.h"

ReportWindow::ReportWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::ReportWindow)
{
    ui->setupUi(this);
    setReportWindowConfig();
    setDefaultReportWindowStatus();
}

ReportWindow::~ReportWindow()
{
    delete ui;
    delete menuBar;
    delete parentWidget;
    delete myValidator;
}

void ReportWindow::closeEvent(QCloseEvent *event)
{
    sendSignalToMainWindowCloseEvent();
}

void ReportWindow::setReportWindowConfig()
{
    setWindowTitle("Звітність");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    menuBar = new QMenuBar();
    setMenuBar(menuBar);

    QAction *adminWindowAction = new QAction("Повернутись");
    menuBar->addAction(adminWindowAction);

    connect(adminWindowAction, &QAction::triggered, this, &ReportWindow::slotSignalToMainWindowCloseEvent);
}

void ReportWindow::setDefaultReportWindowStatus()
{
    const QList<QLineEdit*> lineEdits = ReportWindow::findChildren<QLineEdit*>();
    for (QLineEdit* lineEdit : lineEdits)
    {
        lineEdit->clear();
        lineEdit->clearFocus();
    }
}

void ReportWindow::slotSignalToMainWindowCloseEvent()
{
    sendSignalToMainWindowCloseEvent();
}

void ReportWindow::on_pushButton_clicked()
{
    if (ui->frame->layout())
    {
        QLayout* layout = ui->frame->layout();
        while (QLayoutItem* item = layout->takeAt(0))
        {
            delete item->widget();
            delete item;
        }
        delete layout;
    }

    QHBoxLayout *layout = new QHBoxLayout(ui->frame);

    if(ui->radioButton_1->isChecked())
    {
        QSqlQuery query(QSqlDatabase::database("MyDatabase"));

        // Виконуємо запит для отримання кількості оформлень кожного абонемента
        query.prepare("SELECT s.subscription_title, COUNT(sc.subscriptionclient_subscription_id) AS total_subscriptions "
                      "FROM subscription s "
                      "LEFT JOIN subscriptionclient sc ON s.subscription_id = sc.subscriptionclient_subscription_id "
                      "GROUP BY s.subscription_id, s.subscription_title");

        if (!query.exec())
        {
            qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text();
                return;
        }

        QChart *chart = new QChart();
        chart->setTitle("Гістограма з підрахунком кількості оформлень кожного абонемента");

        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        chart->addAxis(axisX, Qt::AlignBottom);

        QValueAxis *axisY = new QValueAxis();
        chart->addAxis(axisY, Qt::AlignLeft);

        QBarSeries *series = new QBarSeries();

        while (query.next())
        {
            QString subscriptionTitle = query.value("subscription_title").toString();
            int totalSubscriptions = query.value("total_subscriptions").toInt();

            QBarSet *barSet = new QBarSet(subscriptionTitle);
            *barSet << totalSubscriptions;

            series->append(barSet);
            axisX->append(subscriptionTitle);
        }

        chart->addSeries(series);
        series->attachAxis(axisX);
        series->attachAxis(axisY);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        layout->addWidget(chartView);
    }

    if(ui->radioButton_2->isChecked())
    {
        QSqlQuery query(QSqlDatabase::database("MyDatabase"));

        query.prepare("SELECT a.admin_id, CONCAT(a.admin_lastname, ' ', LEFT(a.admin_firstname, 1), '.', LEFT(a.admin_middlename, 1), '.') AS admin_name, "
                      "COUNT(sc.subscriptionclient_subscription_id) AS total_subscriptions "
                      "FROM admin a "
                      "LEFT JOIN subscriptionclient sc ON a.admin_id = sc.subscriptionclient_admin_id "
                      "GROUP BY a.admin_id, admin_name");

        if (!query.exec())
        {
            qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text();
                return;
        }

        QChart *chart = new QChart();
        chart->setTitle("Гістограма з підрахунком кількості виданих абонементів кожним адміністратором");

        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        chart->addAxis(axisX, Qt::AlignBottom);

        QValueAxis *axisY = new QValueAxis();
        chart->addAxis(axisY, Qt::AlignLeft);

        QBarSeries *series = new QBarSeries();

        while (query.next())
        {
            QString adminName = query.value("admin_name").toString();
            int totalSubscriptions = query.value("total_subscriptions").toInt();

            QBarSet *barSet = new QBarSet(adminName);
            *barSet << totalSubscriptions;

            series->append(barSet);
            axisX->append(adminName);
        }

        chart->addSeries(series);
        series->attachAxis(axisX);
        series->attachAxis(axisY);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        layout->addWidget(chartView);
    }

}
