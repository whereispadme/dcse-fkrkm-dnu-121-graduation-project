#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::AdminWindow)
{
    ui->setupUi(this);

    parentWidget = new QWidget();
    createAdminWindow = new CreateAdminWindow();
    editAdminWindow = new EditAdminWindow();

    setAdminWindowConfig();
    setLineEditValidator();
    setDefaultAdminWindowStatus();

    adminTableViewAction = new AdminTableViewAction(ui->adminTableView);
    adminTableViewAction->setTableView();

    personalAdminTableViewAction = new PersonalAdminTableViewAction(ui->personalAdminTableView);
    personalAdminTableViewAction->setTableView();

    ui->adminTableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->adminTableView, &QTableView::customContextMenuRequested, [&](const QPoint& pos)
    {
        static QMenu* menu = nullptr;

        QModelIndex index = ui->adminTableView->indexAt(pos);

        if (index.isValid())
        {

        if (!menu)
        {
            menu = new QMenu();

            QAction *action1 = new QAction("Створити адміністратора", parentWidget);
            menu->addAction(action1);

            connect(action1, &QAction::triggered, this, &AdminWindow::on_createAdminPushButton_clicked);

            QAction *action2 = new QAction("Редагувати адміністратора", parentWidget);
            menu->addAction(action2);

            connect(action2, &QAction::triggered, this, &AdminWindow::on_editAdminPushButton_clicked);

            QAction *action3 = new QAction("Видалити адміністратора", parentWidget);
            menu->addAction(action3);

            connect(action3, &QAction::triggered, this, &AdminWindow::on_removeAdminPushButton_clicked);
        }
            menu->popup(ui->adminTableView->viewport()->mapToGlobal(pos));
        }
    });

    connect(createAdminWindow, &CreateAdminWindow::sendSignalToAdminWindowCloseEvent, this, &AdminWindow::getSignalFromCreateAdminWindowCloseEvent);
    connect(createAdminWindow, &CreateAdminWindow::sendSignalToAdminWindowPushButtonClicked, this, &AdminWindow::getSignalFromCreateAdminWindowPushButtonClicked);

    connect(editAdminWindow, &EditAdminWindow::sendSignalToAdminWindowCloseEvent, this, &AdminWindow::getSignalFromEditAdminWindowCloseEvent);
    connect(editAdminWindow, &EditAdminWindow::sendSignalToAdminWindowPushButtonClicked, this, &AdminWindow::getSignalFromEditAdminWindowPushButtonClicked);

    QModelIndex myIndex = ui->adminTableView->model()->index(ui->adminTableView->currentIndex().row(), 0, QModelIndex());
    QVariant admin_id = ui->adminTableView->model()->data(myIndex);

    personalAdminTableViewAction->searchRecord(admin_id.toString());
}

AdminWindow::~AdminWindow()
{
    delete ui;
    delete menuBar;
    delete parentWidget;
    delete myValidator;
    delete adminTableViewAction;
}

void AdminWindow::closeEvent(QCloseEvent *event)
{
    sendSignalToMainWindowCloseEvent();
}

void AdminWindow::setAdminWindowConfig()
{
    setWindowTitle("Адміністратори");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    menuBar = new QMenuBar();
    setMenuBar(menuBar);

    QAction *adminWindowAction = new QAction("Повернутись");
    menuBar->addAction(adminWindowAction);

    connect(adminWindowAction, &QAction::triggered, this, &AdminWindow::slotSignalToMainWindowCloseEvent);
}

void AdminWindow::setDefaultAdminWindowStatus()
{
    const QList<QLineEdit*> lineEdits = AdminWindow::findChildren<QLineEdit*>();
    for (QLineEdit* lineEdit : lineEdits)
    {
        lineEdit->clear();
        lineEdit->clearFocus();
    }

    ui->horizontalLayoutWidget_2->setEnabled(true);
    ui->mainadminCheckBox->setCheckState(Qt::Unchecked);
}

void AdminWindow::setLineEditValidator()
{
    myValidator->setGeneralSearchLineEditValidator(ui->generalLineEdit);
    myValidator->setLoginLineEditValidator(ui->loginLineEdit);
    myValidator->setCyrillicLineEditValidator(ui->lastnameLineEdit, 20);
    myValidator->setCyrillicLineEditValidator(ui->firstnameLineEdit, 15);
    myValidator->setCyrillicLineEditValidator(ui->middlenameLineEdit, 20);
}

void AdminWindow::checkLineEditCorrectInput()
{
    if(!ui->generalLineEdit->text().isEmpty())
        ui->horizontalLayoutWidget_2->setEnabled(false);
    else
        ui->horizontalLayoutWidget_2->setEnabled(true);

    if(!ui->loginLineEdit->text().isEmpty() || !ui->lastnameLineEdit->text().isEmpty() || !ui->firstnameLineEdit->text().isEmpty() || !ui->middlenameLineEdit->text().isEmpty())
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

void AdminWindow::generalLineEditAction()
{
    checkLineEditCorrectInput();

    if(ui->generalLineEdit->text().isEmpty())
    {
        adminTableViewAction->setTableView();
        return;
    }

    if(ui->mainadminCheckBox->isChecked() && ui->adminCheckBox->isChecked())
    {
        adminTableViewAction->generalSearchRecordsWithoutRole(ui->generalLineEdit->text());
        return;
    }
    else if(ui->mainadminCheckBox->isChecked() || ui->adminCheckBox->isChecked())
    {
        (ui->mainadminCheckBox->isChecked() && !ui->adminCheckBox->isChecked()) ? role = "Головний адміністратор" : role = "Адміністратор";
                                                                                                                        adminTableViewAction->generalSearchRecordsWithRole(ui->generalLineEdit->text(), role);
        return;
    }
    else if(!ui->mainadminCheckBox->isChecked() && !ui->adminCheckBox->isChecked())
    {
        adminTableViewAction->generalSearchRecordsWithRole(ui->generalLineEdit->text(), role);
        return;
    }
}

void AdminWindow::filtersLineEditAction()
{
    checkLineEditCorrectInput();

    if(ui->loginLineEdit->text().isEmpty() && ui->lastnameLineEdit->text().isEmpty() && ui->firstnameLineEdit->text().isEmpty() && ui->middlenameLineEdit->text().isEmpty())
    {
        adminTableViewAction->setTableView();
        return;
    }

    if(ui->mainadminCheckBox->isChecked() && ui->adminCheckBox->isChecked())
    {
        adminTableViewAction->filterSearchRecordsWithoutRole(Admin(ui->loginLineEdit->text(), QString(), Initials(ui->lastnameLineEdit->text(), ui->firstnameLineEdit->text(), ui->middlenameLineEdit->text()), role, PersonalAdmin("", "", "")));
        return;
    }
    else if(ui->mainadminCheckBox->isChecked() || ui->adminCheckBox->isChecked())
    {
        (ui->mainadminCheckBox->isChecked() && !ui->adminCheckBox->isChecked()) ? role = "Головний адміністратор" : role = "Адміністратор";
                                                                                                                        adminTableViewAction->filterSearchRecordsWithRole(Admin(ui->loginLineEdit->text(), QString(), Initials(ui->lastnameLineEdit->text(), ui->firstnameLineEdit->text(), ui->middlenameLineEdit->text()), role, PersonalAdmin("", "", "")));
        return;
    }
    else if(!ui->mainadminCheckBox->isChecked() && !ui->adminCheckBox->isChecked())
    {
        adminTableViewAction->filterSearchRecordsWithRole(Admin(ui->loginLineEdit->text(), QString(), Initials(ui->lastnameLineEdit->text(), ui->firstnameLineEdit->text(), ui->middlenameLineEdit->text()), role, PersonalAdmin("", "", "")));
        return;
    }
}

void AdminWindow::checkBoxAction()
{
    if(ui->generalLineEdit->text().isEmpty() &&
        ui->loginLineEdit->text().isEmpty() &&
        ui->lastnameLineEdit->text().isEmpty() &&
        ui->firstnameLineEdit->text().isEmpty() &&
        ui->middlenameLineEdit->text().isEmpty())
    {
        adminTableViewAction->setTableView();
        return;
    }

    if(!ui->generalLineEdit->text().isEmpty())
    {
        if(ui->mainadminCheckBox->isChecked() && ui->adminCheckBox->isChecked())
        {
            adminTableViewAction->generalSearchRecordsWithoutRole(ui->generalLineEdit->text());
            return;
        }
        else
        {
            (ui->mainadminCheckBox->isChecked() && !ui->adminCheckBox->isChecked()) ? role = "Головний адміністратор" : role = "Адміністратор";
                                                                                                                            adminTableViewAction->generalSearchRecordsWithRole(ui->generalLineEdit->text(), role);
            return;
        }
    }
    else
    {
        if(ui->mainadminCheckBox->isChecked() && ui->adminCheckBox->isChecked())
        {
            adminTableViewAction->filterSearchRecordsWithoutRole(Admin(ui->loginLineEdit->text(), QString(), Initials(ui->lastnameLineEdit->text(), ui->firstnameLineEdit->text(), ui->middlenameLineEdit->text()), role, PersonalAdmin("", "", "")));
            return;
        }
        else
        {
            (ui->mainadminCheckBox->isChecked() && !ui->adminCheckBox->isChecked()) ? role = "Головний адміністратор" : role = "Адміністратор";
                                                                                                                            adminTableViewAction->filterSearchRecordsWithRole(Admin(ui->loginLineEdit->text(), QString(), Initials(ui->lastnameLineEdit->text(), ui->firstnameLineEdit->text(), ui->middlenameLineEdit->text()), role, PersonalAdmin("", "", "")));
            return;
        }
    }
}

void AdminWindow::slotSignalToMainWindowCloseEvent()
{
    sendSignalToMainWindowCloseEvent();
}

void AdminWindow::getSignalFromCreateAdminWindowCloseEvent()
{
    createAdminWindow->hide();
    this->show();
}

void AdminWindow::getSignalFromCreateAdminWindowPushButtonClicked()
{
    createAdminWindow->hide();
    this->show();

    admin = createAdminWindow->getCreatedAdminData();

    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("insert into admin (admin_login, admin_password, admin_lastname, admin_firstname, admin_middlename, admin_role) "
                  "values (:login, :password, :lastname, :firstname, :middlename, :role);");

    query.bindValue(":login", admin.getLogin());
    query.bindValue(":password", admin.getPassword());
    query.bindValue(":lastname", admin.getInitials().lastname);
    query.bindValue(":firstname", admin.getInitials().firstname);
    query.bindValue(":middlename", admin.getInitials().middlename);
    query.bindValue(":role", admin.getRole());

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    query.prepare("insert into personaladmin (personaladmin_passport, personaladmin_telephone, personaladmin_adress) "
                  "values (:passport, :telephone, :adress);");

    query.bindValue(":passport", admin.getPersonal().getPassport());
    query.bindValue(":telephone", admin.getPersonal().getTelephone());
    query.bindValue(":adress", admin.getPersonal().getAdress());

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    adminTableViewAction->setTableView();

    if(ui->adminTableView->size().isEmpty())
    {
        personalAdminTableViewAction->searchRecord("***");
    }

    QModelIndex myIndex = ui->adminTableView->model()->index(ui->adminTableView->currentIndex().row(), 0, QModelIndex());
    QVariant admin_id = ui->adminTableView->model()->data(myIndex);

    personalAdminTableViewAction->searchRecord(admin_id.toString());
}

void AdminWindow::getSignalFromEditAdminWindowPushButtonClicked()
{
    editAdminWindow->hide();
    this->show();

    admin = editAdminWindow->getEditedAdminData();

    QModelIndex myIndex = ui->adminTableView->model()->index(ui->adminTableView->currentIndex().row(), 0, QModelIndex());
    QVariant admin_id = ui->adminTableView->model()->data(myIndex);

    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("update admin set admin_login = :login, admin_password = :password, "
                  "admin_lastname = :lastname, admin_firstname = :firstname, admin_middlename = :middlename, "
                  "admin_role = :role where admin_id = :id;");

    query.bindValue(":id", admin_id);
    query.bindValue(":login", admin.getLogin());
    query.bindValue(":password", admin.getPassword());
    query.bindValue(":lastname", admin.getInitials().lastname);
    query.bindValue(":firstname", admin.getInitials().firstname);
    query.bindValue(":middlename", admin.getInitials().middlename);
    query.bindValue(":role", admin.getRole());

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    query.prepare("update personaladmin set personaladmin_passport = :passport, personaladmin_telephone = :telephone, personaladmin_adress = :adress "
                  "where personaladmin_admin_id = :id;");

    query.bindValue(":id", admin_id);
    query.bindValue(":passport", admin.getPersonal().getPassport());
    query.bindValue(":telephone", admin.getPersonal().getTelephone());
    query.bindValue(":adress", admin.getPersonal().getAdress());

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    adminTableViewAction->setTableView();

    if(ui->adminTableView->size().isEmpty())
    {
        personalAdminTableViewAction->searchRecord("***");
    }

    myIndex = ui->adminTableView->model()->index(ui->adminTableView->currentIndex().row(), 0, QModelIndex());
    admin_id = ui->adminTableView->model()->data(myIndex);

    personalAdminTableViewAction->searchRecord(admin_id.toString());
}

void AdminWindow::getSignalFromEditAdminWindowCloseEvent()
{
    editAdminWindow->hide();
    this->show();
}

void AdminWindow::on_generalLineEdit_textEdited(const QString &arg1)
{
    generalLineEditAction();
}

void AdminWindow::on_loginLineEdit_textEdited(const QString &arg1)
{
    filtersLineEditAction();
}

void AdminWindow::on_lastnameLineEdit_textEdited(const QString &arg1)
{
    filtersLineEditAction();
}

void AdminWindow::on_firstnameLineEdit_textEdited(const QString &arg1)
{
    filtersLineEditAction();
}

void AdminWindow::on_middlenameLineEdit_textEdited(const QString &arg1)
{
    filtersLineEditAction();
}

void AdminWindow::on_createAdminPushButton_clicked()
{
    this->hide();
    createAdminWindow->show();
}

void AdminWindow::on_editAdminPushButton_clicked()
{
    this->hide();
    editAdminWindow->show();
}

void AdminWindow::on_removeAdminPushButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Видалення адміністратора", "Ви дійсно бажаєте видалити даного адміністратора?", QMessageBox::Yes | QMessageBox::Cancel);

    if (reply == QMessageBox::Yes)
    {
        QModelIndex myIndex = ui->adminTableView->model()->index(ui->adminTableView->currentIndex().row(), 0, QModelIndex());
        QVariant admin_id = ui->adminTableView->model()->data(myIndex);

        QSqlQuery query(QSqlDatabase::database("MyDatabase"));

        query.prepare("select * from admin where admin_login = :login;");
        query.bindValue(":login", currentAdminLogin);

        if (query.exec() && query.next())
        {
            QMessageBox::critical(this, "Помилка видалення адміністратора", "Активного адміністратора видалити неможливо!");
            return;
        }

        query.prepare("select subscriptionclient_subscription_id from subscriptionclient where subscriptionclient_admin_id = :id and subscriptionclient_end >= CURDATE();");
        query.bindValue(":id", admin_id);

        if (query.exec() && query.next())
        {
            QMessageBox::critical(this, "Помилка видалення адміністратора", "Неможливо видалити адміністратора, оскільки видані ним абонементи наразі активні!");
            return;
        }

        query.prepare("delete from personaladmin where personaladmin_admin_id = :id;");
        query.bindValue(":id", admin_id);

        if (!query.exec())
        {
            qDebug() << "Помилка виконання SQL-запиту1:" << query.lastError().text();
                return;
        }

        query.prepare("delete from admin where admin_id = :id;");
        query.bindValue(":id", admin_id);

        if (!query.exec())
        {
            qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text();
                return;
        }

        QMessageBox::information(this, "Видалення адміністратора", "Адміністратор був успішно видалений!");
        adminTableViewAction->setTableView();

        if (ui->adminTableView->size().isEmpty())
        {
            personalAdminTableViewAction->searchRecord("***");
        }

        myIndex = ui->adminTableView->model()->index(ui->adminTableView->currentIndex().row(), 0, QModelIndex());
        admin_id = ui->adminTableView->model()->data(myIndex);

        personalAdminTableViewAction->searchRecord(admin_id.toString());
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

void AdminWindow::on_mainadminCheckBox_clicked()
{
    checkBoxAction();
}

void AdminWindow::on_adminCheckBox_clicked()
{
    checkBoxAction();
}

void AdminWindow::on_adminTableView_clicked(const QModelIndex &index)
{
    QModelIndex myIndex = ui->adminTableView->model()->index(ui->adminTableView->currentIndex().row(), 0, QModelIndex());
    QVariant admin_id = ui->adminTableView->model()->data(myIndex);

    personalAdminTableViewAction->searchRecord(admin_id.toString());
}

void AdminWindow::setCurrentAdminLogin(QString login)
{
    currentAdminLogin = login;
}
