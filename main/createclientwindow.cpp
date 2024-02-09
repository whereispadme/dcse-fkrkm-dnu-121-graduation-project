#include "createclientwindow.h"
#include "ui_createclientwindow.h"

CreateClientWindow::CreateClientWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::CreateClientWindow)
{
    ui->setupUi(this);

    parentWidget = new QWidget();
    myValidator = new MyValidator();

    setCreateClientWindowConfig();
    setDefaultCreateClientWindowStatus();
    setLineEditValidator();
}

CreateClientWindow::~CreateClientWindow()
{
    delete ui;
    delete myValidator;
    delete menuBar;
    delete parentWidget;
}

void CreateClientWindow::closeEvent(QCloseEvent *event)
{
    sendSignalToClientWindowCloseEvent();
}

void CreateClientWindow::setCreateClientWindowConfig()
{
    setWindowTitle("Зареєструвати клієнта");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    menuBar = new QMenuBar();
    setMenuBar(menuBar);

    QAction *CreateClientWindowAction = new QAction("Повернутись");
    menuBar->addAction(CreateClientWindowAction);

    connect(CreateClientWindowAction, &QAction::triggered, this, &CreateClientWindow::slotSignalToClientWindowCloseEvent);
}

void CreateClientWindow::setDefaultCreateClientWindowStatus()
{
    const QList<QLineEdit*> lineEdits = CreateClientWindow::findChildren<QLineEdit*>();
    for (QLineEdit* lineEdit : lineEdits)
    {
        lineEdit->clear();
        lineEdit->clearFocus();
    }

    ui->maleRadioButton->setChecked(true);
    ui->lastnameLineEdit->setFocus();

    QDate currentDate = QDate::currentDate();
    ui->birthdayDateEdit->setDate(currentDate);
    ui->startDateEdit->setDate(currentDate);
    ui->endDateEdit->setDate(currentDate);

    ui->applyPushButton->setEnabled(false);
    ui->createClientPushButton->setEnabled(false);
}

void CreateClientWindow::setLineEditValidator()
{
    myValidator->setCyrillicLineEditValidator(ui->lastnameLineEdit, 20);
    myValidator->setCyrillicLineEditValidator(ui->firstnameLineEdit, 15);
    myValidator->setCyrillicLineEditValidator(ui->middlenameLineEdit, 20);
    myValidator->setIntegerLineEditValidator(ui->passportLineEdit, 9);
    ui->telephoneLineEdit->setInputMask("+38\\0 (99) 999 99 99");

    myValidator->setAdressLineEditValidator(ui->doctorLineEdit);
    myValidator->setAdressLineEditValidator(ui->decisionLineEdit);
}

void CreateClientWindow::checkLineEditCorrectInput(int type)
{
    if(type == 0)
    {
        if( ui->lastnameLineEdit->text().isEmpty() ||
            ui->firstnameLineEdit->text().isEmpty() ||
            ui->middlenameLineEdit->text().isEmpty() ||
            ui->passportLineEdit->text().isEmpty() ||
            ui->passportLineEdit->text().size() != 9 ||
            ui->telephoneLineEdit->text().size() != 19)
        {
            ui->applyPushButton->setEnabled(false);
            return;
        }
        else
        {
            ui->applyPushButton->setEnabled(true);
        }
    }
    else
    {
        if( ui->institutionLineEdit->text().isEmpty() ||
            ui->doctorLineEdit->text().isEmpty() ||
            ui->decisionLineEdit->text().isEmpty())
        {
            ui->createClientPushButton->setEnabled(false);
            return;
        }
        else
        {
            ui->createClientPushButton->setEnabled(true);
        }
    }
}

Client CreateClientWindow::getCreatedClientData()
{
    Initials initials;
    initials.lastname = ui->lastnameLineEdit->text();
    initials.firstname = ui->firstnameLineEdit->text();
    initials.middlename = ui->middlenameLineEdit->text();

    QString gender;
    (ui->maleRadioButton->isChecked()) ? gender = "Чоловіча" : gender = "Жіноча";

    PersonalClient personalClient;
    personalClient.setPassport(ui->passportLineEdit->text());
    personalClient.setTelephone(ui->telephoneLineEdit->text());
    personalClient.setBirthday(ui->birthdayDateEdit->text());

    MedicalData medicalData;
    medicalData.setInstitution(ui->institutionLineEdit->text());
    medicalData.setDoctor(ui->doctorLineEdit->text());
    medicalData.setDateissue(ui->startDateEdit->text());
    medicalData.setDateexpiration(ui->endDateEdit->text());
    medicalData.setDecision(ui->decisionLineEdit->text());

    return Client(initials, gender, personalClient, medicalData);
}

void CreateClientWindow::slotSignalToClientWindowCloseEvent()
{
    if(ui->stackedWidget->widget(1)->isActiveWindow()) ui->stackedWidget->setCurrentWidget(ui->clientWidget);
    sendSignalToClientWindowCloseEvent();
}

void CreateClientWindow::on_applyPushButton_clicked()
{

    QSqlQuery checkQuery(QSqlDatabase::database("MyDatabase"));

    checkQuery.prepare("SELECT personalclient_client_id FROM personalclient WHERE personalclient_passport = :passport");
    checkQuery.bindValue(":passport", ui->passportLineEdit->text());
    if (checkQuery.exec() && checkQuery.next())
    {
        QMessageBox::critical(this, "Помилка створення клієнта", "Клієнт з таким номером паспорта вже існує у системі!");
        ui->stackedWidget->setCurrentWidget(ui->clientWidget);
        return;
    }

    checkQuery.prepare("SELECT personalclient_client_id FROM personalclient WHERE personalclient_telephone = :telephone");
    checkQuery.bindValue(":telephone", ui->telephoneLineEdit->text());
    if (checkQuery.exec() && checkQuery.next())
    {
        QMessageBox::critical(this, "Помилка створення клієнта", "Клієнт з таким номером телефону вже існує у системі!");
        ui->stackedWidget->setCurrentWidget(ui->clientWidget);
        return;
    }

    ui->stackedWidget->setCurrentWidget(ui->medicalDataWidget);
}

void CreateClientWindow::on_createClientPushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->clientWidget);
    sendSignalToClientWindowPushButtonClicked();
}

void CreateClientWindow::on_lastnameLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput(0);
}

void CreateClientWindow::on_firstnameLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput(0);
}

void CreateClientWindow::on_middlenameLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput(0);
}

void CreateClientWindow::on_passportLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput(0);
}

void CreateClientWindow::on_telephoneLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput(0);
}

void CreateClientWindow::on_institutionLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput(1);
}

void CreateClientWindow::on_doctorLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput(1);
}

void CreateClientWindow::on_decisionLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput(1);
}
