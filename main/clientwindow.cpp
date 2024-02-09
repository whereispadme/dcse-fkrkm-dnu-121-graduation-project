#include "clientwindow.h"
#include "ui_clientwindow.h"

ClientWindow::ClientWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::ClientWindow)
{
    ui->setupUi(this);

    parentWidget = new QWidget();
    createClientWindow = new CreateClientWindow();
    editClientWindow = new EditClientWindow();
    resetMedicalDataWindow = new ResetMedicalDataWindow();

    setClientWindowConfig();
    setLineEditValidator();
    setDefaultClientWindowStatus();
    
    clientTableViewAction = new ClientTableViewAction(ui->clientTableView);
    clientTableViewAction->setTableView();

    personalClientTableViewAction = new PersonalClientTableViewAction(ui->personalClientTableView);
    personalClientTableViewAction->setTableView();

    medicalDataTableViewAction = new MedicalDataTableViewAction(ui->medicalDataTableView);
    medicalDataTableViewAction->setTableView();

    myValidator = new MyValidator();

    ui->clientTableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->clientTableView, &QTableView::customContextMenuRequested, [&](const QPoint& pos)
            {
                static QMenu* menu = nullptr;
        
        QModelIndex index = ui->clientTableView->indexAt(pos);

                if (index.isValid())
                {

                    if (!menu)
                    {
                        menu = new QMenu();

                        QAction *action1 = new QAction("Зареєструвати клієнта", parentWidget);
                        menu->addAction(action1);
                        connect(action1, &QAction::triggered, this, &ClientWindow::on_createClientPushButton_clicked);

                        QAction *action2 = new QAction("Редагувати клієнта", parentWidget);
                        menu->addAction(action2);
                        connect(action2, &QAction::triggered, this, &ClientWindow::on_editClientPushButton_clicked);

                        QAction *action3 = new QAction("Видалити клієнта", parentWidget);
                        menu->addAction(action3);
                        connect(action3, &QAction::triggered, this, &ClientWindow::on_removeClientPushButton_clicked);

                        QAction *action4 = new QAction("Оновити медичну довідку", parentWidget);
                        menu->addAction(action4);
                        connect(action4, &QAction::triggered, this, &ClientWindow::on_resetMedicalDataPushButton_clicked);
                    }
                    menu->popup(ui->clientTableView->viewport()->mapToGlobal(pos));
                }
            });

    connect(createClientWindow, &CreateClientWindow::sendSignalToClientWindowCloseEvent, this, &ClientWindow::getSignalFromCreateClientWindowCloseEvent);
    connect(createClientWindow, &CreateClientWindow::sendSignalToClientWindowPushButtonClicked, this, &ClientWindow::getSignalFromCreateClientWindowPushButtonClicked);

    connect(editClientWindow, &EditClientWindow::sendSignalToClientWindowCloseEvent, this, &ClientWindow::getSignalFromEditClientWindowCloseEvent);
    connect(editClientWindow, &EditClientWindow::sendSignalToClientWindowPushButtonClicked, this, &ClientWindow::getSignalFromEditClientWindowPushButtonClicked);

    connect(resetMedicalDataWindow, &ResetMedicalDataWindow::sendSignalToClientWindowCloseEvent, this, &ClientWindow::getSignalFromResetMedicalDataWindowCloseEvent);
    connect(resetMedicalDataWindow, &ResetMedicalDataWindow::sendSignalToClientWindowPushButtonClicked, this, &ClientWindow::getSignalFromResetMedicalDataWindowPushButtonClicked);

    QModelIndex myIndex = ui->clientTableView->model()->index(ui->clientTableView->currentIndex().row(), 0, QModelIndex());
    QVariant client_id = ui->clientTableView->model()->data(myIndex);

    personalClientTableViewAction->searchRecord(client_id.toString());
    medicalDataTableViewAction->searchRecord(client_id.toString());
}

ClientWindow::~ClientWindow()
{
    delete ui;
    delete createClientWindow;
    delete editClientWindow;
    delete resetMedicalDataWindow;
    delete menuBar;
    delete parentWidget;
    delete myValidator;
}

void ClientWindow::closeEvent(QCloseEvent *event)
{
    sendSignalToMainWindowCloseEvent();
}

void ClientWindow::setClientWindowConfig()
{
    setWindowTitle("Клієнти");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    menuBar = new QMenuBar();
    setMenuBar(menuBar);

    QAction *clienWindowAction = new QAction("Повернутись");
    menuBar->addAction(clienWindowAction);

    connect(clienWindowAction, &QAction::triggered, this, &ClientWindow::slotSignalToMainWindowCloseEvent);
}

void ClientWindow::setDefaultClientWindowStatus()
{
    const QList<QLineEdit*> lineEdits = ClientWindow::findChildren<QLineEdit*>();
    for (QLineEdit* lineEdit : lineEdits)
    {
        lineEdit->clear();
        lineEdit->clearFocus();
    }
}

void ClientWindow::setLineEditValidator()
{
    myValidator->setGeneralSearchLineEditValidator(ui->generalLineEdit);
    myValidator->setCyrillicLineEditValidator(ui->lastnameLineEdit, 20);
    myValidator->setCyrillicLineEditValidator(ui->firstnameLineEdit, 15);
    myValidator->setCyrillicLineEditValidator(ui->middlenameLineEdit, 20);
}

void ClientWindow::checkLineEditCorrectInput()
{
    if(!ui->generalLineEdit->text().isEmpty())
        ui->horizontalLayoutWidget_2->setEnabled(false);
    else
        ui->horizontalLayoutWidget_2->setEnabled(true);

    if(!ui->lastnameLineEdit->text().isEmpty() || !ui->firstnameLineEdit->text().isEmpty() || !ui->middlenameLineEdit->text().isEmpty())
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

void ClientWindow::generalLineEditAction()
{
    checkLineEditCorrectInput();

    if(ui->generalLineEdit->text().isEmpty())
    {
        clientTableViewAction->setTableView();
        return;
    }

    if(ui->maleCheckBox->isChecked() && ui->femaleCheckBox->isChecked())
    {
        clientTableViewAction->generalSearchRecordsWithoutGender(ui->generalLineEdit->text());
        return;
    }
    else if(ui->maleCheckBox->isChecked() || ui->femaleCheckBox->isChecked())
    {
        (ui->maleCheckBox->isChecked() && !ui->femaleCheckBox->isChecked()) ? gender = "Чоловіча" : gender = "Жіноча";
        clientTableViewAction->generalSearchRecordsWithGender(ui->generalLineEdit->text(), gender);
        return;
    }
    else if(!ui->maleCheckBox->isChecked() && !ui->femaleCheckBox->isChecked())
    {
        clientTableViewAction->generalSearchRecordsWithGender(ui->generalLineEdit->text(), gender);
        return;
    }
}

void ClientWindow::filtersLineEditAction()
{
    checkLineEditCorrectInput();

    if(ui->lastnameLineEdit->text().isEmpty() && ui->firstnameLineEdit->text().isEmpty() && ui->middlenameLineEdit->text().isEmpty())
    {
        clientTableViewAction->setTableView();
        return;
    }

    if(ui->maleCheckBox->isChecked() && ui->femaleCheckBox->isChecked())
    {
        clientTableViewAction->filterSearchRecordsWithoutGender(Client(Initials(ui->lastnameLineEdit->text(), ui->firstnameLineEdit->text(), ui->middlenameLineEdit->text()), gender, PersonalClient("", "", ""), MedicalData()));
        return;
    }
    else if(ui->maleCheckBox->isChecked() || ui->femaleCheckBox->isChecked())
    {
        (ui->maleCheckBox->isChecked() && !ui->femaleCheckBox->isChecked()) ? gender = "Чоловіча" : gender = "Жіноча";
        clientTableViewAction->filterSearchRecordsWithGender(Client(Initials(ui->lastnameLineEdit->text(), ui->firstnameLineEdit->text(), ui->middlenameLineEdit->text()), gender, PersonalClient("", "", ""), MedicalData()));
        return;
    }
    else if(!ui->maleCheckBox->isChecked() && !ui->femaleCheckBox->isChecked())
    {
        clientTableViewAction->filterSearchRecordsWithGender(Client(Initials(ui->lastnameLineEdit->text(), ui->firstnameLineEdit->text(), ui->middlenameLineEdit->text()), gender, PersonalClient("", "", ""), MedicalData()));
        return;
    }
}


void ClientWindow::checkBoxAction()
{
    if(ui->generalLineEdit->text().isEmpty() &&
        ui->lastnameLineEdit->text().isEmpty() &&
        ui->firstnameLineEdit->text().isEmpty() &&
        ui->middlenameLineEdit->text().isEmpty())
    {
        clientTableViewAction->setTableView();
        return;
    }

    if(!ui->generalLineEdit->text().isEmpty())
    {
        if(ui->maleCheckBox->isChecked() && ui->femaleCheckBox->isChecked())
        {
            clientTableViewAction->generalSearchRecordsWithoutGender(ui->generalLineEdit->text());
            return;
        }
        else
        {
            (ui->maleCheckBox->isChecked() && !ui->femaleCheckBox->isChecked()) ? gender = "Чоловіча" : gender = "Жіноча";
            clientTableViewAction->generalSearchRecordsWithGender(ui->generalLineEdit->text(), gender);
            return;
        }
    }
    else
    {
        if(ui->maleCheckBox->isChecked() && ui->femaleCheckBox->isChecked())
        {
            clientTableViewAction->filterSearchRecordsWithoutGender(Client(Initials(ui->lastnameLineEdit->text(), ui->firstnameLineEdit->text(), ui->middlenameLineEdit->text()), gender, PersonalClient("", "", ""), MedicalData()));
            return;
        }
        else
        {
            (ui->maleCheckBox->isChecked() && !ui->femaleCheckBox->isChecked()) ? gender = "Чоловіча" : gender = "Жіноча";
            clientTableViewAction->filterSearchRecordsWithGender(Client(Initials(ui->lastnameLineEdit->text(), ui->firstnameLineEdit->text(), ui->middlenameLineEdit->text()), gender, PersonalClient("", "", ""), MedicalData()));
            return;
        }
    }
}

void ClientWindow::slotSignalToMainWindowCloseEvent()
{
    sendSignalToMainWindowCloseEvent();
}

void ClientWindow::getSignalFromCreateClientWindowCloseEvent()
{
    createClientWindow->hide();
    this->show();
}

void ClientWindow::getSignalFromCreateClientWindowPushButtonClicked()
{
    createClientWindow->hide();
    this->show();

    client = createClientWindow->getCreatedClientData();

    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("insert into client (client_lastname, client_firstname, client_middlename, client_gender) "
                  "values (:lastname, :firstname, :middlename, :gender);");

    query.bindValue(":lastname", client.getInitials().lastname);
    query.bindValue(":firstname", client.getInitials().firstname);
    query.bindValue(":middlename", client.getInitials().middlename);
    query.bindValue(":gender", client.getGender());

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    query.prepare("insert into personalclient (personalclient_passport, personalclient_telephone, personalclient_birthday) "
                  "values (:passport, :telephone, :birthday);");

    query.bindValue(":passport", client.getPersonal().getPassport());
    query.bindValue(":telephone", client.getPersonal().getTelephone());
    query.bindValue(":birthday", client.getPersonal().getBirthday());

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    query.prepare("insert into medicaldata (medicaldata_institution, medicaldata_doctor, medicaldata_dateissue, medicaldata_dateexpiration, medicaldata_decision) "
                  "values (:institution, :doctor, :dateissue, :dateexpiration, :decision);");

    query.bindValue(":institution", client.getMedicalData().getInstitution());
    query.bindValue(":doctor", client.getMedicalData().getDoctor());
    query.bindValue(":dateissue", client.getMedicalData().getDateissue());
    query.bindValue(":dateexpiration", client.getMedicalData().getDateexpiration());
    query.bindValue(":decision", client.getMedicalData().getDecision());

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }


    clientTableViewAction->setTableView();

    if(ui->clientTableView->size().isEmpty())
    {
        personalClientTableViewAction->searchRecord("***");
        medicalDataTableViewAction->searchRecord("***");
    }

    QModelIndex myIndex = ui->clientTableView->model()->index(ui->clientTableView->currentIndex().row(), 0, QModelIndex());
    QVariant client_id = ui->clientTableView->model()->data(myIndex);

    personalClientTableViewAction->searchRecord(client_id.toString());
    medicalDataTableViewAction->searchRecord(client_id.toString());

    sendSignalToMainWindowResetClientTableView();
}

void ClientWindow::getSignalFromEditClientWindowCloseEvent()
{
    editClientWindow->hide();
    this->show();
}

void ClientWindow::getSignalFromEditClientWindowPushButtonClicked()
{
    editClientWindow->hide();
    this->show();

    client = editClientWindow->getEditedClientData();
    
    QModelIndex myIndex = ui->clientTableView->model()->index(ui->clientTableView->currentIndex().row(), 0, QModelIndex());
    QVariant client_id = ui->clientTableView->model()->data(myIndex);

    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("update client set client_lastname = :lastname, client_firstname = :firstname, client_middlename = :middlename, "
                  "client_gender = :gender where client_id = :id;");

    query.bindValue(":id", client_id);
    query.bindValue(":lastname", client.getInitials().lastname);
    query.bindValue(":firstname", client.getInitials().firstname);
    query.bindValue(":middlename", client.getInitials().middlename);
    query.bindValue(":gender", client.getGender());

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    query.prepare("update personalclient set personalclient_passport = :passport, personalclient_telephone = :telephone, personalclient_birthday = :birthday "
                  "where personalclient_client_id = :id;");

    query.bindValue(":id", client_id);
    query.bindValue(":passport", client.getPersonal().getPassport());
    query.bindValue(":telephone", client.getPersonal().getTelephone());
    query.bindValue(":birthday", client.getPersonal().getBirthday());

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    clientTableViewAction->setTableView();

    if(ui->clientTableView->size().isEmpty())
    {
        personalClientTableViewAction->searchRecord("***");
        medicalDataTableViewAction->searchRecord("***");
    }

    myIndex = ui->clientTableView->model()->index(ui->clientTableView->currentIndex().row(), 0, QModelIndex());
    client_id = ui->clientTableView->model()->data(myIndex);

    personalClientTableViewAction->searchRecord(client_id.toString());
    medicalDataTableViewAction->searchRecord(client_id.toString());

    sendSignalToMainWindowResetClientTableView();
}

void ClientWindow::getSignalFromResetMedicalDataWindowCloseEvent()
{
    this->resetMedicalDataWindow->hide();
    this->show();
}

void ClientWindow::getSignalFromResetMedicalDataWindowPushButtonClicked()
{
    this->resetMedicalDataWindow->hide();
    this->show();

    medicalData = resetMedicalDataWindow->getEditedMedicalData();

    QModelIndex myIndex = ui->clientTableView->model()->index(ui->clientTableView->currentIndex().row(), 0, QModelIndex());
    QVariant client_id = ui->clientTableView->model()->data(myIndex);

    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("update medicaldata set medicaldata_institution = :institution, "
                  "medicaldata_doctor = :doctor, "
                  "medicaldata_dateissue = :dateissue, "
                  "medicaldata_dateexpiration = :dateexpiration, "
                  "medicaldata_decision = :decision where medicaldata_сlient_id = :client_id;");

    query.bindValue(":institution", medicalData.getInstitution());
    query.bindValue(":doctor", medicalData.getDoctor());
    query.bindValue(":dateissue", medicalData.getDateissue());
    query.bindValue(":dateexpiration", medicalData.getDateexpiration());
    query.bindValue(":decision", medicalData.getDecision());
    query.bindValue(":client_id", client_id);

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    clientTableViewAction->setTableView();

    if(ui->clientTableView->size().isEmpty())
    {
        personalClientTableViewAction->searchRecord("***");
        medicalDataTableViewAction->searchRecord("***");
    }

    myIndex = ui->clientTableView->model()->index(ui->clientTableView->currentIndex().row(), 0, QModelIndex());
    client_id = ui->clientTableView->model()->data(myIndex);

    personalClientTableViewAction->searchRecord(client_id.toString());
    medicalDataTableViewAction->searchRecord(client_id.toString());

    sendSignalToMainWindowResetClientTableView();
}

void ClientWindow::on_createClientPushButton_clicked()
{
    this->hide();
    createClientWindow->show();
}

void ClientWindow::on_editClientPushButton_clicked()
{
    this->hide();
    editClientWindow->show();
}

void ClientWindow::on_removeClientPushButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Видалення адміністратора", "Ви дійсно хочете видалити даного клієнта?", QMessageBox::Yes | QMessageBox::Cancel);

    if (reply == QMessageBox::Yes)
    {
    }
    else if (reply == QMessageBox::Cancel)
    {
        return;
    }
    else
    {
        return;
    }

    QModelIndex myIndex = ui->clientTableView->model()->index(ui->clientTableView->currentIndex().row(), 0, QModelIndex());
    QVariant client_id = ui->clientTableView->model()->data(myIndex);

    QSqlQuery checkQuery(QSqlDatabase::database("MyDatabase"));

    checkQuery.prepare("SELECT COUNT(*) FROM subscriptionclient WHERE subscriptionclient_client_id = :clientId");
    checkQuery.bindValue(":clientId", client_id);
    if (checkQuery.exec() && checkQuery.next())
    {
        int activeSubscriptionsCount = checkQuery.value(0).toInt();
        if (activeSubscriptionsCount > 0)
        {
            QMessageBox::critical(this, "Помилка видалення клієнта", "Клієнт має активні абонементи і не може бути видалений!");
            return;
        }
    }

    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("delete from medicaldata where medicaldata_сlient_id = :id;");
    query.bindValue(":id", client_id);

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    query.prepare("delete from personalclient where personalclient_client_id = :id;");
    query.bindValue(":id", client_id);

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    query.prepare("delete from client where client_id = :id;");
    query.bindValue(":id", client_id);

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    clientTableViewAction->setTableView();

    if(ui->clientTableView->size().isEmpty())
    {
        personalClientTableViewAction->searchRecord("***");
        medicalDataTableViewAction->searchRecord("***");
    }

    myIndex = ui->clientTableView->model()->index(ui->clientTableView->currentIndex().row(), 0, QModelIndex());
    client_id = ui->clientTableView->model()->data(myIndex);

    personalClientTableViewAction->searchRecord(client_id.toString());
    medicalDataTableViewAction->searchRecord(client_id.toString());

    sendSignalToMainWindowResetClientTableView();
}

void ClientWindow::on_generalLineEdit_textEdited(const QString &arg1)
{
    generalLineEditAction();
}

void ClientWindow::on_lastnameLineEdit_textEdited(const QString &arg1)
{
    filtersLineEditAction();
}

void ClientWindow::on_firstnameLineEdit_textEdited(const QString &arg1)
{
    filtersLineEditAction();
}

void ClientWindow::on_middlenameLineEdit_textEdited(const QString &arg1)
{
    filtersLineEditAction();
}

void ClientWindow::on_maleCheckBox_clicked()
{
    checkBoxAction();
}

void ClientWindow::on_femaleCheckBox_clicked()
{
    checkBoxAction();
}

void ClientWindow::on_resetMedicalDataPushButton_clicked()
{

    QModelIndex myIndex = ui->clientTableView->model()->index(ui->clientTableView->currentIndex().row(), 0, QModelIndex());
    QVariant client_id = ui->clientTableView->model()->data(myIndex);

    QSqlQuery checkQuery(QSqlDatabase::database("MyDatabase"));
    checkQuery.prepare("SELECT medicaldata_dateexpiration FROM medicaldata WHERE medicaldata_сlient_id = :clientId");
        checkQuery.bindValue(":clientId", client_id);

    if (checkQuery.exec() && checkQuery.next())
    {
        QDate expirationDate = checkQuery.value("medicaldata_dateexpiration").toDate();
        QDate currentDate = QDate::currentDate();

        // Проверка наличия предыдущей медицинской справки
        if (expirationDate >= currentDate)
        {
            QMessageBox::critical(this, "Помилка оновлення медичної довідки", "Неможливо оновити медичну довідку, оскільки попередня ще не закінчилася.");
            return;
        }
    }

    resetMedicalDataWindow->show();
    this->hide();
}

void ClientWindow::on_clientTableView_clicked(const QModelIndex &index)
{
    QModelIndex myIndex = ui->clientTableView->model()->index(ui->clientTableView->currentIndex().row(), 0, QModelIndex());
    QVariant client_id = ui->clientTableView->model()->data(myIndex);

    personalClientTableViewAction->searchRecord(client_id.toString());
    medicalDataTableViewAction->searchRecord(client_id.toString());
}
