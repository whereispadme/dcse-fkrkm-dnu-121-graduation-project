#include "subscriptionwindow.h"
#include "ui_subscriptionwindow.h"

SubscriptionWindow::SubscriptionWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::SubscriptionWindow)
{
    ui->setupUi(this);

    parentWidget = new QWidget();
    createSubscriptionWindow = new CreateSubscriptionWindow();
    editSubscriptionWindow = new EditSubscriptionWindow();
    myValidator = new MyValidator();

    setSubscriptionWindowConfig();
    setLineEditValidator();
    setDefaultSubscriptionWindowStatus();

    subscriptionTableViewAction = new SubscriptionTableViewAction(ui->subscriptionTableView);
    subscriptionTableViewAction->setTableView();

    subscriptionclientTableViewAction = new SubscriptionClientTableViewAction(ui->subscriptionclientTableView);
    subscriptionclientTableViewAction->setTableView();

    ui->subscriptionTableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->subscriptionTableView, &QTableView::customContextMenuRequested, [&](const QPoint& pos)
            {
                static QMenu* menu = nullptr;

                QModelIndex index = ui->subscriptionTableView->indexAt(pos);

                if (index.isValid())
                {

                    if (!menu)
                    {
                        menu = new QMenu();

                        QAction *action1 = new QAction("Створити абонемент", parentWidget);
                        menu->addAction(action1);

                        connect(action1, &QAction::triggered, this, &SubscriptionWindow::on_createSubPushButton_clicked);

                        QAction *action2 = new QAction("Редагувати абонемент", parentWidget);
                        menu->addAction(action2);

                        connect(action2, &QAction::triggered, this, &SubscriptionWindow::on_editSubPushButton_clicked);

                        QAction *action3 = new QAction("Видалити абонемент", parentWidget);
                        menu->addAction(action3);

                        connect(action3, &QAction::triggered, this, &SubscriptionWindow::on_removeSubPushButton_clicked);
                    }
                    menu->popup(ui->subscriptionTableView->viewport()->mapToGlobal(pos));
                }
            });

    connect(createSubscriptionWindow, &CreateSubscriptionWindow::sendSignalToSubscriptionWindowCloseEvent, this, &SubscriptionWindow::getSignalFromCreateSubscriptionWindowCloseEvent);
    connect(createSubscriptionWindow, &CreateSubscriptionWindow::sendSignalToSubscriptionWindowPushButtonClicked, this, &SubscriptionWindow::getSignalFromCreateSubscriptionWindowPushButtonClicked);

    connect(editSubscriptionWindow, &EditSubscriptionWindow::sendSignalToSubscriptionWindowCloseEvent, this, &SubscriptionWindow::getSignalFromEditSubscriptionWindowCloseEvent);
    connect(editSubscriptionWindow, &EditSubscriptionWindow::sendSignalToSubscriptionWindowPushButtonClicked, this, &SubscriptionWindow::getSignalFromEditSubscriptionWindowPushButtonClicked);
}

SubscriptionWindow::~SubscriptionWindow()
{
    delete ui;
    delete menuBar;
    delete parentWidget;
    delete myValidator;
}

void SubscriptionWindow::closeEvent(QCloseEvent *event)
{
    sendSignalToMainWindowCloseEvent();
}

void SubscriptionWindow::setSubscriptionWindowConfig()
{
    setWindowTitle("Абонементи");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    menuBar = new QMenuBar();
    setMenuBar(menuBar);

    QAction *adminWindowAction = new QAction("Повернутись");
    menuBar->addAction(adminWindowAction);

    connect(adminWindowAction, &QAction::triggered, this, &SubscriptionWindow::slotSignalToMainWindowCloseEvent);
}

void SubscriptionWindow::setDefaultSubscriptionWindowStatus()
{
    const QList<QLineEdit*> lineEdits = SubscriptionWindow::findChildren<QLineEdit*>();
    for (QLineEdit* lineEdit : lineEdits)
    {
        lineEdit->clear();
        lineEdit->clearFocus();
    }
}

void SubscriptionWindow::setLineEditValidator()
{

}

void SubscriptionWindow::checkLineEditCorrectInput()
{
    if(!ui->generalLineEdit->text().isEmpty())
        ui->horizontalLayoutWidget_2->setEnabled(false);
    else
        ui->horizontalLayoutWidget_2->setEnabled(true);

    if(!ui->titleLineEdit->text().isEmpty() || !ui->trainingAmountLineEdit->text().isEmpty() || !ui->priceLineEdit->text().isEmpty())
    {
        ui->general->setEnabled(false);
        ui->generalLineEdit->setEnabled(false);
    }
    else
    {
        ui->general->setEnabled(true);
        ui->generalLineEdit->setEnabled(true);
    }
}

void SubscriptionWindow::checkClearLineEditForResetTableView()
{
    if(ui->generalLineEdit->text().isEmpty() &&
        ui->titleLineEdit->text().isEmpty() &&
        ui->trainingAmountLineEdit->text().isEmpty() &&
        ui->priceLineEdit->text().isEmpty())
    {
        subscriptionTableViewAction->setTableView();
    }
    else
    {
        return;
    }
}

void SubscriptionWindow::generalLineEditAction()
{
    checkLineEditCorrectInput();
    QString type;

    if(ui->generalLineEdit->text().isEmpty())
    {
        subscriptionTableViewAction->setTableView();
        return;
    }

    if(ui->unlimitedCheckBox->isChecked() && ui->limitedCheckBox->isChecked())
    {
        subscriptionTableViewAction->generalSearchRecordsWithoutType(ui->generalLineEdit->text());
        return;
    }
    else if(ui->unlimitedCheckBox->isChecked() || ui->limitedCheckBox->isChecked())
    {
        (ui->unlimitedCheckBox->isChecked() && !ui->limitedCheckBox->isChecked()) ? type = "Безлімітний" : type = "Обмежений";
        subscriptionTableViewAction->generalSearchRecordsWithType(ui->generalLineEdit->text(), type);
        return;
    }
    else if(!ui->unlimitedCheckBox->isChecked() && !ui->limitedCheckBox->isChecked())
    {
        subscriptionTableViewAction->generalSearchRecordsWithType(ui->generalLineEdit->text(), type);
        return;
    }
}

void SubscriptionWindow::filtersLineEditAction()
{
    checkLineEditCorrectInput();
    QString type;

    if(ui->titleLineEdit->text().isEmpty() && ui->trainingAmountLineEdit->text().isEmpty() && ui->priceLineEdit->text().isEmpty())
    {
        subscriptionTableViewAction->setTableView();
        return;
    }

    if(ui->unlimitedCheckBox->isChecked() && ui->limitedCheckBox->isChecked())
    {
        subscriptionTableViewAction->filterSearchRecordsWithoutType(Subscription(ui->titleLineEdit->text(),
                                                                                 type,
                                                                                 "",
                                                                                 "",
                                                                                 ui->trainingAmountLineEdit->text(),
                                                                                 "",
                                                                                 ui->priceLineEdit->text()));
        return;
    }
    else if(ui->unlimitedCheckBox->isChecked() || ui->limitedCheckBox->isChecked())
    {
        (ui->unlimitedCheckBox->isChecked() && !ui->limitedCheckBox->isChecked()) ? type = "Безлімітний" : type = "Обмежений";
        subscriptionTableViewAction->filterSearchRecordsWithType(Subscription(ui->titleLineEdit->text(),
                                                                              type,
                                                                              "",
                                                                              "",
                                                                              ui->trainingAmountLineEdit->text(),
                                                                              "",
                                                                              ui->priceLineEdit->text()));
        return;
    }
    else if(!ui->unlimitedCheckBox->isChecked() && !ui->limitedCheckBox->isChecked())
    {
        subscriptionTableViewAction->filterSearchRecordsWithType(Subscription(ui->titleLineEdit->text(),
                                                                              type,
                                                                              "",
                                                                              "",
                                                                              ui->trainingAmountLineEdit->text(),
                                                                              "",
                                                                              ui->priceLineEdit->text()));
        return;
    }
}

void SubscriptionWindow::checkBoxAction()
{
    checkLineEditCorrectInput();
    QString type;

    if(ui->generalLineEdit->text().isEmpty() &&
        ui->titleLineEdit->text().isEmpty() &&
        ui->trainingAmountLineEdit->text().isEmpty() &&
        ui->priceLineEdit->text().isEmpty())
    {
        subscriptionTableViewAction->setTableView();
        return;
    }

    if(!ui->generalLineEdit->text().isEmpty())
    {
        if(ui->unlimitedCheckBox->isChecked() && ui->limitedCheckBox->isChecked())
        {
            subscriptionTableViewAction->generalSearchRecordsWithoutType(ui->generalLineEdit->text());
            return;
        }
        else
        {
            (ui->unlimitedCheckBox->isChecked() && !ui->limitedCheckBox->isChecked()) ? type = "Безлімітний" : type = "Обмежений";
            subscriptionTableViewAction->generalSearchRecordsWithType(ui->generalLineEdit->text(), type);
            return;
        }
    }
    else
    {
        if(ui->unlimitedCheckBox->isChecked() && ui->limitedCheckBox->isChecked())
        {
            subscriptionTableViewAction->filterSearchRecordsWithoutType(Subscription(ui->titleLineEdit->text(),
                                                                                     type,
                                                                                     "",
                                                                                     "",
                                                                                     ui->trainingAmountLineEdit->text(),
                                                                                     "",
                                                                                     ui->priceLineEdit->text()));
            return;
        }
        else
        {
            (ui->unlimitedCheckBox->isChecked() && !ui->limitedCheckBox->isChecked()) ? type = "Безлімітний" : type = "Обмежений";
            subscriptionTableViewAction->filterSearchRecordsWithType(Subscription(ui->titleLineEdit->text(),
                                                                                  type,
                                                                                  "",
                                                                                  "",
                                                                                  ui->trainingAmountLineEdit->text(),
                                                                                  "",
                                                                                  ui->priceLineEdit->text()));
            return;
        }
    }
}

void SubscriptionWindow::slotSignalToMainWindowCloseEvent()
{
    sendSignalToMainWindowCloseEvent();
}

void SubscriptionWindow::getSignalFromCreateSubscriptionWindowCloseEvent()
{
    createSubscriptionWindow->hide();
    this->show();
}

void SubscriptionWindow::getSignalFromCreateSubscriptionWindowPushButtonClicked()
{
    createSubscriptionWindow->hide();
    this->show();

    subscription = createSubscriptionWindow->getCreatedSubscriptionData();

    QModelIndex myIndex = ui->subscriptionTableView->model()->index(ui->subscriptionTableView->currentIndex().row(), 0, QModelIndex());
    QVariant sub_id = ui->subscriptionTableView->model()->data(myIndex);

    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("INSERT INTO subscription (subscription_title, subscription_type, subscription_timestart, subscription_timeend, subscription_days, subscription_trainingamount, subscription_price) "
                  "VALUES (:title, :s_type, :timestart, :timeend, :days, :trainingamount, :price);");

    query.bindValue(":title", subscription.getTitle());
    query.bindValue(":s_type", subscription.getType());
    query.bindValue(":timestart", subscription.getStart());
    query.bindValue(":timeend", subscription.getEnd());
    query.bindValue(":trainingamount", subscription.getTrainingAmount());
    query.bindValue(":days", subscription.getDays());
    query.bindValue(":price", subscription.getPrice());

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    subscriptionTableViewAction->setTableView();

    sendSignalToMainWindowResetTableView();
}

void SubscriptionWindow::getSignalFromEditSubscriptionWindowCloseEvent()
{
    editSubscriptionWindow->hide();
    this->show();
}

void SubscriptionWindow::getSignalFromEditSubscriptionWindowPushButtonClicked()
{
    editSubscriptionWindow->hide();
    this->show();

    subscription = editSubscriptionWindow->getEditedSubscriptionData();

    QModelIndex myIndex = ui->subscriptionTableView->model()->index(ui->subscriptionTableView->currentIndex().row(), 0, QModelIndex());
    QVariant sub_id = ui->subscriptionTableView->model()->data(myIndex);

    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("update subscription set subscription_title = :title, subscription_type = :s_type, subscription_trainingamount = :trainingamount, "
                  "subscription_days = :days, subscription_price = :price where subscription_id = :id;");

    query.bindValue(":id", sub_id);
    query.bindValue(":title", subscription.getTitle());
    query.bindValue(":s_type", subscription.getType());
    query.bindValue(":trainingamount", subscription.getTrainingAmount());
    query.bindValue(":days", subscription.getDays());
    query.bindValue(":price", subscription.getPrice());

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    subscriptionTableViewAction->setTableView();

    sendSignalToMainWindowResetTableView();
}

void SubscriptionWindow::on_generalLineEdit_textEdited(const QString &arg1)
{
    generalLineEditAction();
}

void SubscriptionWindow::on_titleLineEdit_textEdited(const QString &arg1)
{
    filtersLineEditAction();
}

void SubscriptionWindow::on_trainingAmountLineEdit_textEdited(const QString &arg1)
{
    filtersLineEditAction();
}

void SubscriptionWindow::on_priceLineEdit_textEdited(const QString &arg1)
{
    filtersLineEditAction();
}

void SubscriptionWindow::on_unlimitedCheckBox_stateChanged(int arg1)
{
    checkBoxAction();
}

void SubscriptionWindow::on_limitedCheckBox_stateChanged(int arg1)
{
    checkBoxAction();
}

void SubscriptionWindow::on_createSubPushButton_clicked()
{
    this->hide();
    createSubscriptionWindow->show();
}

void SubscriptionWindow::on_editSubPushButton_clicked()
{
    QModelIndex myIndex = ui->subscriptionTableView->model()->index(ui->subscriptionTableView->currentIndex().row(), 0, QModelIndex());
    QVariant sub_id = ui->subscriptionTableView->model()->data(myIndex);

    QSqlQuery checkQuery(QSqlDatabase::database("MyDatabase"));
    checkQuery.prepare("SELECT COUNT(*) FROM subscriptionclient WHERE subscriptionclient_subscription_id = :subscriptionId");
    checkQuery.bindValue(":subscriptionId", sub_id);

    if (checkQuery.exec() && checkQuery.next())
    {
        int count = checkQuery.value(0).toInt();

        // Проверка количества связанных клиентов для абонемента
        if (count > 0)
        {
            // Вывод сообщения о невозможности редактирования абонемента, так как есть связанные клиенты
            QMessageBox::critical(this, "Помилка редагування абонемента", "Неможливо редагувати абонемент, так як на нього оформлені клієнти.");
            return;
        }
    }

    this->hide();
    editSubscriptionWindow->show();

    sendSignalToMainWindowResetTableView();
}

void SubscriptionWindow::on_removeSubPushButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Видалення абонемента", "Ви дійсно хочете видалити даний абонемент?", QMessageBox::Yes | QMessageBox::Cancel);

    if (reply == QMessageBox::Yes)
    {
        QModelIndex myIndex = ui->subscriptionTableView->model()->index(ui->subscriptionTableView->currentIndex().row(), 0, QModelIndex());
        QVariant sub_id = ui->subscriptionTableView->model()->data(myIndex);

        QSqlQuery query(QSqlDatabase::database("MyDatabase"));

        // Проверка наличия оформлений абонемента
        query.prepare("SELECT COUNT(*) FROM subscriptionclient WHERE subscriptionclient_subscription_id = :id;");
        query.bindValue(":id", sub_id);

        if (!query.exec() || !query.next())
        {
            qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text();
                return;
        }

        int subscriptionClientsCount = query.value(0).toInt();

        if (subscriptionClientsCount > 0)
        {
            QMessageBox::warning(this, "Видалення абонемента", "Неможливо видалити абонемент, оскільки він має оформлення.");
            return;
        }

        // Удаление абонемента
        query.prepare("delete from subscription where subscription_id = :id;");
        query.bindValue(":id", sub_id);

        if (!query.exec())
        {
            qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text();
                return;
        }

        subscriptionTableViewAction->setTableView();

        sendSignalToMainWindowResetTableView();
    }
    else if (reply == QMessageBox::Cancel)
    {
        return;
    }
    else
    {
        return;
    }
}

void SubscriptionWindow::on_subscriptionTableView_clicked(const QModelIndex &index)
{
    QModelIndex myIndex = ui->subscriptionTableView->model()->index(ui->subscriptionTableView->currentIndex().row(), 0, QModelIndex());
    QVariant subscription_id = ui->subscriptionTableView->model()->data(myIndex);

    subscriptionclientTableViewAction->searchRecord(subscription_id.toString());
}
