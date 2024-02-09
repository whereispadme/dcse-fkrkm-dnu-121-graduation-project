#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setDatabaseConnect();

    authWindow = new AuthWindow();
    clientWindow = new ClientWindow();
    subscriptionWindow = new SubscriptionWindow();
    adminWindow = new AdminWindow();
    reportWindow = new ReportWindow();
    myValidator = new MyValidator();

    parentWidget = new QWidget();

    subclientClientTableView = new ClientTableViewAction(ui->subclientClientTableView);
    subclientClientTableView->setTableView();

    clientTableViewAction2 = new ClientTableViewAction(ui->checkClientTableView);
    clientTableViewAction2->setTableView();

    clientTableViewAction3 = new ClientTableViewAction(ui->medicaldataClientTableView);
    clientTableViewAction3->setTableView();

    clientTableViewAction4 = new ClientTableViewAction(ui->fastSearchTableView);
    clientTableViewAction4->setTableView();

    subclientSubscriptionTableViewAction = new SubscriptionTableViewAction(ui->subclientSubscriptionTableView);
    subclientSubscriptionTableViewAction->setTableView();

    fastSearchSubscriptionTableViewAction = new SubscriptionTableViewAction(ui->fastSearchTableView);
    fastSearchSubscriptionClientTableViewAction = new SubscriptionClientTableViewAction(ui->fastSearchTableView);
    fastSearchClientTableViewAction = new ClientTableViewAction(ui->fastSearchTableView);
    fastSearchClientTableViewAction->setTableView();

    setMainWindowMenu();
    setMainWindowConfig();
    setLineEditValidator();
    setDefaultMainWindowStatus();

    connect(authWindow, &AuthWindow::sendSignalToMainWindowApplyPushButtonClicked, this, &MainWindow::getSignalFromAuthWindowApplyPushButtonClicked);
    connect(clientWindow, &ClientWindow::sendSignalToMainWindowCloseEvent, this, &MainWindow::getSignalFromClientWindowCloseEvent);
    connect(subscriptionWindow, &SubscriptionWindow::sendSignalToMainWindowCloseEvent, this, &MainWindow::getSignalFromSubscriptionWindowCloseEvent);
    connect(adminWindow, &AdminWindow::sendSignalToMainWindowCloseEvent, this, &MainWindow::getSignalFromAdminWindowCloseEvent);
    connect(reportWindow, &ReportWindow::sendSignalToMainWindowCloseEvent, this, &MainWindow::getSignalFromReportWindowCloseEvent);

    connect(clientWindow, &ClientWindow::sendSignalToMainWindowResetClientTableView, this, &MainWindow::getSignalFromClientWindowResetClientTableView);
    connect(subscriptionWindow, &SubscriptionWindow::sendSignalToMainWindowResetTableView, this, &MainWindow::getSignalFromSubscriptionWindowResetTableView);

    this->hide();
    authWindow->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete authWindow;
    delete adminWindow;

    delete subclientClientTableView;
    delete subclientSubscriptionTableViewAction;

    delete parentWidget;
    delete myValidator;

    delete fastSearchSubscriptionTableViewAction;
    delete fastSearchSubscriptionClientTableViewAction;
    delete fastSearchClientTableViewAction;
}

bool MainWindow::setDatabaseConnect()
{
    this->database = QSqlDatabase::addDatabase("QODBC", "MyDatabase");

    QString connect = "DRIVER={MySQL ODBC 8.0 Unicode Driver};";

    connect.append("server = localhost, 3306;");
    connect.append("database = graduateproject;");
    connect.append("user = root;");
    connect.append("password = 23kapkap;");
    connect.append("multi_host = 1;");

    database.setDatabaseName(connect);

    if(!database.open())
    {
        qDebug() << "Помилка підключення до бази даних!";
        return false;
    }

    return true;
}

void MainWindow::setMainWindowConfig()
{
    setWindowTitle("КущевськийАндрій, ПЗ-19-1");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowIcon(QIcon(":/icons/mainwindow.png"));
}

void MainWindow::setMainWindowMenu()
{
    QAction *clienWindowAction = ui->menubar->addAction("Клієнти");
    clienWindowAction->setParent(parentWidget);
    connect(clienWindowAction, &QAction::triggered, this, &MainWindow::showClientWindow);

    QAction *subscriptionWindowAction = ui->menubar->addAction("Абонементи");
    subscriptionWindowAction->setParent(parentWidget);
    connect(subscriptionWindowAction, &QAction::triggered, this, &MainWindow::showSubscriptionWindow);

    QAction *adminWindowAction = ui->menubar->addAction("Адміністратори");
    adminWindowAction->setParent(parentWidget);
    connect(adminWindowAction, &QAction::triggered, this, &MainWindow::showAdminWindow);

    QAction *reportWindowAction = ui->menubar->addAction("Звітність");
    reportWindowAction->setParent(parentWidget);
    connect(reportWindowAction, &QAction::triggered, this, &MainWindow::showReportWindow);

    QAction *quitAction = ui->menubar->addAction("Завершити роботу програми");
    quitAction->setParent(parentWidget);
    connect(quitAction, &QAction::triggered, this, &QApplication::quit);
}

void MainWindow::setDefaultMainWindowStatus()
{
    const QList<QLineEdit*> lineEdits = MainWindow::findChildren<QLineEdit*>();
    for (QLineEdit* lineEdit : lineEdits)
    {
        lineEdit->clear();
        lineEdit->clearFocus();
    }

    ui->subclientClientTableView->clearSelection();
    ui->subclientSubscriptionTableView->clearSelection();
}

void MainWindow::setLineEditValidator()
{
    myValidator->setGeneralSearchLineEditValidator(ui->subclientGeneralClientLineEdit);
    myValidator->setGeneralSearchLineEditValidator(ui->checkGeneralLineEdit);

    myValidator->setCyrillicLineEditValidator(ui->createclientLastnameLineEdit, 20);
    myValidator->setCyrillicLineEditValidator(ui->createclientFirstnameLineEdit, 15);
    myValidator->setCyrillicLineEditValidator(ui->createclientMiddlenameLineEdit, 20);
    myValidator->setIntegerLineEditValidator(ui->createclientPassportLineEdit, 9);
    ui->createclientTelephoneLineEdit->setInputMask("+38\\0 (99) 999 99 99");
    myValidator->setAdressLineEditValidator(ui->createclientInstitutionLineEdit);
    myValidator->setAdressLineEditValidator(ui->createclientDoctorLineEdit);
    myValidator->setAdressLineEditValidator(ui->createclientDecisionLineEdit);
}

void MainWindow::showClientWindow()
{
    this->hide();
    clientWindow->show();
}

void MainWindow::showSubscriptionWindow()
{
    this->hide();
    subscriptionWindow->show();
}

void MainWindow::showAdminWindow()
{
    QSqlQuery query(QSqlDatabase::database("MyDatabase"));
    query.prepare("SELECT admin_role FROM admin WHERE admin_login = :adminlogin");
    query.bindValue(":adminlogin", currentAdmin.getLogin());

    if (query.exec() && query.next())
    {
        QString adminRole = query.value("admin_role").toString();

        if (adminRole != "Головний адміністратор")
        {
           QMessageBox::critical(this, "Помилка доступу", "У вас недостатньо прав для доступу до меню адміністраторів!");
           return;
        }
    }

    this->hide();
    adminWindow->setCurrentAdminLogin(currentAdmin.getLogin());
    adminWindow->show();
}

void MainWindow::showReportWindow()
{
    this->hide();
    reportWindow->show();
}

void MainWindow::getSignalFromAuthWindowApplyPushButtonClicked()
{
    QString currentLogin = authWindow->getCurrentLogin();
    QString currentPassword = authWindow->getCurrentPassword();

    currentAdmin.setLogin(currentLogin);
    currentAdmin.setPassword(currentPassword);

    QString queryText = "select * from Admin where admin_login = '%1' and admin_password = '%2';";
    QString formattedQueryText = queryText.arg(currentLogin, currentPassword);

    QSqlQuery query(formattedQueryText, QSqlDatabase::database("MyDatabase"));

    if (query.next())
    {
        authWindow->hide();
        this->show();

        qDebug() << "Успішна авторизація!";
    }
    else
    {
        qDebug() << "Помилка авторизації: невірний логін або пароль!";

        QMessageBox messageBox;
        messageBox.setWindowTitle("Помилка авторизації");
        messageBox.setText("Уведено невірний логін або пароль! Будь ласка, спробуйте ще раз!");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.exec();
    }
}

void MainWindow::getSignalFromClientWindowCloseEvent()
{
    clientWindow->hide();
    this->show();
}

void MainWindow::getSignalFromClientWindowResetClientTableView()
{
    subclientClientTableView->setTableView();
    clientTableViewAction2->setTableView();
    clientTableViewAction3->setTableView();
    clientTableViewAction4->setTableView();
}

void MainWindow::getSignalFromSubscriptionWindowCloseEvent()
{
    subscriptionWindow->hide();
    this->show();
}

void MainWindow::getSignalFromSubscriptionWindowResetTableView()
{
    subclientSubscriptionTableViewAction->setTableView();
}

void MainWindow::getSignalFromAdminWindowCloseEvent()
{
    adminWindow->hide();
    this->show();
}

void MainWindow::getSignalFromReportWindowCloseEvent()
{
    reportWindow->hide();
    this->show();
}

void MainWindow::on_createClientPushButton_clicked()
{
    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("insert into medicaldata (medicaldata_institution, medicaldata_doctor, medicaldata_dateissue, medicaldata_dateexpiration, medicaldata_decision) "
                  "values (:institution, :doctor, :dateissue, :dateexpiration, :decision);");

    query.bindValue(":institution", ui->institutionLineEdit->text());
    query.bindValue(":doctor", ui->doctorLineEdit->text());
    query.bindValue(":dateissue", ui->createclientStartDateEdit->text());
    query.bindValue(":dateexpiration", ui->createclientEndDateEdit->text());
    query.bindValue(":decision", ui->createclientDecisionLineEdit->text());

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    ui->stackedWidget_2->setCurrentWidget(ui->page_3);
}

void MainWindow::on_subclientGeneralClientLineEdit_textEdited(const QString &arg1)
{
    if(ui->subclientGeneralClientLineEdit->text().isEmpty())
    {
        subclientClientTableView->setTableView();
        return;
    }

    subclientClientTableView->generalSearchRecordsWithoutGender(ui->subclientGeneralClientLineEdit->text());
    return;
}

void MainWindow::on_subclientGeneralSubscriptionLineEdit_textEdited(const QString &arg1)
{
    if(ui->subclientGeneralSubscriptionLineEdit->text().isEmpty())
    {
        subclientSubscriptionTableViewAction->setTableView();
        return;
    }

    subclientSubscriptionTableViewAction->generalSearchRecordsWithoutType(ui->subclientGeneralSubscriptionLineEdit->text());
    return;
}

void MainWindow::on_subclientApplyPushButton_clicked()
{    
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Оформлення абонемента", "Ви дійсно бажаєте оформити абонемент на даного клієнта?", QMessageBox::Yes | QMessageBox::Cancel);

    if (reply == QMessageBox::Yes)
    {
        QMessageBox::information(this, "Оформлення абонемента", "Абонемент був успішно оформлений!");
    }
    else if (reply == QMessageBox::Cancel)
    {
        return;
    }
    else
    {
        return;
    }

    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    QModelIndex myIndex = ui->subclientSubscriptionTableView->model()->index(ui->subclientSubscriptionTableView->currentIndex().row(), 0, QModelIndex());
    QVariant subscription_id = ui->subclientSubscriptionTableView->model()->data(myIndex);

    myIndex = ui->subclientClientTableView->model()->index(ui->subclientClientTableView->currentIndex().row(), 0, QModelIndex());
    QVariant client_id = ui->subclientClientTableView->model()->data(myIndex);

    QString admin_id;

    QSqlQuery checkQuery(QSqlDatabase::database("MyDatabase"));
    checkQuery.prepare("SELECT medicaldata_dateexpiration FROM medicaldata WHERE medicaldata_сlient_id = :clientId");
        checkQuery.bindValue(":clientId", client_id);

    if (checkQuery.exec() && checkQuery.next())
    {
        QDate expirationDate = checkQuery.value("medicaldata_dateexpiration").toDate();
        QDate currentDate = QDate::currentDate();

        // Проверка просроченной медицинской справки
        if (expirationDate < currentDate)
        {
           QMessageBox::critical(this, "Помилка видання абонемента", "Неможливо видати абонемент, оскільки у клієнта просрочена медична довідка.");
           return;
        }
    }

    checkQuery.prepare("SELECT COUNT(*) FROM subscriptionclient WHERE subscriptionclient_client_id = :clientId");
    checkQuery.bindValue(":clientId", client_id);

    if (checkQuery.exec() && checkQuery.next())
    {
        int count = checkQuery.value(0).toInt();

        // Проверка наличия активного абонемента
        if (count > 0)
        {
           QMessageBox::critical(this, "Помилка видання абонемента", "Неможливо видати абонемент, оскільки у клієнта вже є активний абонемент.");
           return;
        }
    }

    query.exec("select * from admin where admin_login = :login;");
    query.bindValue(":login", authWindow->getCurrentLogin());

    if (query.next())
        admin_id = query.value(0).toString();

    QDate currentDate = QDate::currentDate();
    QString subscriptionclient_start = currentDate.toString("yyyy.MM.dd");

    QDate futureDate = currentDate.addDays(30);
    QString subscriptionclient_end = futureDate.toString("yyyy.MM.dd");

    myIndex = ui->subclientSubscriptionTableView->model()->index(ui->subclientSubscriptionTableView->currentIndex().row(), 6, QModelIndex());
    QVariant subscription_trainingleft = ui->subclientSubscriptionTableView->model()->data(myIndex);

    query.prepare("insert into subscriptionclient "
                  "(subscriptionclient_subscription_id, subscriptionclient_admin_id, subscriptionclient_client_id, "
                  "subscriptionclient_start, subscriptionclient_end, subscriptionclient_trainingleft) "
                  "values (:subscription_id, 1, :client_id, :start, :end, :trainingleft);");

    query.bindValue(":subscription_id", subscription_id);
    query.bindValue(":admin_id", admin_id);
    query.bindValue(":client_id", client_id);
    query.bindValue(":start", subscriptionclient_start);
    query.bindValue(":end", subscriptionclient_end);
    query.bindValue(":trainingleft", subscription_trainingleft);

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }
}

void MainWindow::on_createclientApplyPushButton_clicked()
{   
    QString gender;
    (ui->createclientMaleRadioButton->isChecked()) ? gender = "Чоловіча" : gender = "Жіноча";

    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("SELECT personalclient_client_id FROM personalclient WHERE personalclient_passport = :passport");
    query.bindValue(":passport", ui->createclientPassportLineEdit->text());
    if (query.exec() && query.next())
    {
        QMessageBox::critical(this, "Помилка створення клієнта", "Клієнт з таким номером паспорта вже існує у системі!");
        return;
    }

    query.prepare("SELECT personalclient_client_id FROM personalclient WHERE personalclient_telephone = :telephone");
    query.bindValue(":telephone", ui->createclientTelephoneLineEdit->text());
    if (query.exec() && query.next())
    {
        QMessageBox::critical(this, "Помилка створення клієнта", "Клієнт з таким номером телефону вже існує у системі!");
        return;
    }

    query.prepare("insert into client (client_lastname, client_firstname, client_middlename, client_gender) "
                  "values (:lastname, :firstname, :middlename, :gender);");

    query.bindValue(":lastname", ui->createclientLastnameLineEdit->text());
    query.bindValue(":firstname", ui->createclientFirstnameLineEdit->text());
    query.bindValue(":middlename", ui->createclientMiddlenameLineEdit->text());
    query.bindValue(":gender", gender);

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    query.prepare("insert into personalclient (personalclient_passport, personalclient_telephone, personalclient_birthday) "
                  "values (:passport, :telephone, :birthday);");

    query.bindValue(":passport", ui->createclientPassportLineEdit->text());
    query.bindValue(":telephone", ui->createclientTelephoneLineEdit->text());
    query.bindValue(":birthday", ui->createclientBirthdayDateEdit->text());

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    ui->stackedWidget_2->setCurrentWidget(ui->page_4);
}

void MainWindow::on_checkPushButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Позначення відвідування", "Ви дійсно бажаєте позначити відвідування даного клієнта?", QMessageBox::Yes | QMessageBox::Cancel);

    if (reply == QMessageBox::Yes)
    {

        QModelIndex myIndex = ui->checkClientTableView->model()->index(ui->checkClientTableView->currentIndex().row(), 0, QModelIndex());
        QVariant subscription_client_id = ui->checkClientTableView->model()->data(myIndex);

        QSqlQuery query(QSqlDatabase::database("MyDatabase"));

        // Проверка наличия оформленного абонемента у клиента
        query.prepare("select subscriptionclient_subscription_id from subscriptionclient where subscriptionclient_client_id = :id;");
        query.bindValue(":id", subscription_client_id);

        if (query.exec() && !query.next())
        {
           // Отображение сообщения для администратора
           QMessageBox::information(this, "Немає оформленого абонементу", "У даного клієнта немає оформленого абонементу.");
           return;
        }

        query.prepare("SELECT subscriptionclient_subscription_id FROM subscriptionclient "
                      "INNER JOIN subscription ON subscriptionclient.subscriptionclient_subscription_id = subscription.subscription_id "
                      "WHERE subscriptionclient_client_id = :clientID AND subscription.subscription_type = 'Безлімітний'");
        query.bindValue(":clientID", subscription_client_id);

        if (query.exec() && query.next())
        {
           QMessageBox::information(this, "Безлімітний абонемент", "Даний клієнт має необмежену кількість занять за абонементом! Абонемент буде автоматично видалений після кінця сроку дії!");
           return;
        }

        query.prepare("update subscriptionclient set subscriptionclient_trainingleft = (subscriptionclient_trainingleft - 1)  where subscriptionclient_client_id = :id;");
        query.bindValue(":id", subscription_client_id);

        if (!query.exec())
        {
           qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text();
               return;
        }

        // Проверка на окончание свободных занятий
        query.prepare("select subscriptionclient_trainingleft from subscriptionclient where subscriptionclient_client_id = :id;");
        query.bindValue(":id", subscription_client_id);

        if (query.exec() && query.next())
        {
           int trainingLeft = query.value("subscriptionclient_trainingleft").toInt();

           if (trainingLeft <= 0)
           {
               query.prepare("delete from subscriptionclient where subscriptionclient_client_id = :id;");
               query.bindValue(":id", subscription_client_id);

               if (!query.exec())
               {
                   qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text();
                       return;
               }
               QMessageBox::information(this, "Завершено використання абонементу", "Всі заняття з абонементом використані. Запис про абонемент було видалено.");
           }
        }
        else
        {
           qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text();
        }

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

void MainWindow::on_checkGeneralLineEdit_textEdited(const QString &arg1)
{
    if(ui->checkGeneralLineEdit->text().isEmpty())
    {
        clientTableViewAction2->setTableView();
        return;
    }

    clientTableViewAction2->generalSearchRecordsWithoutGender(ui->checkGeneralLineEdit->text());
    return;
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(ui->comboBox->currentText() == "Клієнти")
    {
        fastSearchClientTableViewAction = new ClientTableViewAction(ui->fastSearchTableView);
        fastSearchClientTableViewAction->setTableView();
    }

    if(ui->comboBox->currentText() == "Абонементи")
    {
        fastSearchSubscriptionTableViewAction = new SubscriptionTableViewAction(ui->fastSearchTableView);
        fastSearchSubscriptionTableViewAction->setTableView();
    }

    if(ui->comboBox->currentText() == "Оформлені абонементи")
    {
        fastSearchSubscriptionClientTableViewAction = new SubscriptionClientTableViewAction(ui->fastSearchTableView);
        fastSearchSubscriptionClientTableViewAction->setTableView();
    }
}

void MainWindow::on_fastSearchGeneralLineEdit_textEdited(const QString &arg1)
{
    if(ui->comboBox->currentText() == "Клієнти")
    {
        if(ui->fastSearchGeneralLineEdit->text().isEmpty())
        {
           fastSearchClientTableViewAction->setTableView();
           return;
        }

        fastSearchClientTableViewAction->generalSearchRecordsWithoutGender(ui->fastSearchGeneralLineEdit->text());
        return;
    }

    if(ui->comboBox->currentText() == "Абонементи")
    {
        if(ui->fastSearchGeneralLineEdit->text().isEmpty())
        {
           fastSearchSubscriptionTableViewAction->setTableView();
           return;
        }

        fastSearchSubscriptionTableViewAction->generalSearchRecordsWithoutType(ui->fastSearchGeneralLineEdit->text());
        return;
    }

    if(ui->comboBox->currentText() == "Оформлені абонементи")
    {
        if(ui->fastSearchGeneralLineEdit->text().isEmpty())
        {
           fastSearchSubscriptionClientTableViewAction->setTableView();
           return;
        }

        fastSearchSubscriptionClientTableViewAction->generalSearchRecord(ui->fastSearchGeneralLineEdit->text());
        return;
    }
}

void MainWindow::on_medicaldataApplyPushButton_clicked()
{
    QModelIndex myIndex = ui->medicaldataClientTableView->model()->index(ui->medicaldataClientTableView->currentIndex().row(), 0, QModelIndex());
    QVariant client_id = ui->medicaldataClientTableView->model()->data(myIndex);

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

    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void MainWindow::on_applyPushButton_clicked()
{
    QModelIndex myIndex = ui->medicaldataClientTableView->model()->index(ui->medicaldataClientTableView->currentIndex().row(), 0, QModelIndex());
    QVariant client_id = ui->medicaldataClientTableView->model()->data(myIndex);

    QSqlQuery query(QSqlDatabase::database("MyDatabase"));

    query.prepare("update medicaldata set medicaldata_institution = :institution, "
                  "medicaldata_doctor = :doctor, "
                  "medicaldata_dateissue = :dateissue, "
                  "medicaldata_dateexpiration = :dateexpiration, "
                  "medicaldata_decision = :decision where medicaldata_сlient_id = :client_id;");

    query.bindValue(":institution", ui->institutionLineEdit->text());
    query.bindValue(":doctor", ui->doctorLineEdit->text());
    query.bindValue(":dateissue", ui->startDateEdit->text());
    query.bindValue(":dateexpiration", ui->endDateEdit->text());
    query.bindValue(":decision", ui->decisionLineEdit->text());
    query.bindValue(":client_id", client_id);

    if (!query.exec())
    {
        qDebug() << "Помилка виконання SQL-запиту:" << query.lastError().text(); return;
    }

    QMessageBox::information(this, "Оновлення медичної довідки", "Медична довідка даного клієнта була успішно оновлена!");
    ui->stackedWidget->setCurrentWidget(ui->page);
}

