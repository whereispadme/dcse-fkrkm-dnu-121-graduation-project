#include "createadminwindow.h"
#include "ui_createadminwindow.h"

CreateAdminWindow::CreateAdminWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::CreateAdminWindow)
{
    ui->setupUi(this);

    parentWidget = new QWidget();
    myValidator = new MyValidator();

    setCreateAdminWindowConfig();
    setDefaultCreateAdminWindowStatus();
    setLineEditValidator();
}

CreateAdminWindow::~CreateAdminWindow()
{
    delete ui;
    delete myValidator;
    delete menuBar;
    delete parentWidget;
    delete myValidator;
}

void CreateAdminWindow::closeEvent(QCloseEvent *event)
{
    sendSignalToAdminWindowCloseEvent();
}

void CreateAdminWindow::setCreateAdminWindowConfig()
{
    setWindowTitle("Створити адміністратора");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    menuBar = new QMenuBar();
    setMenuBar(menuBar);

    QAction *createAdminWindowAction = new QAction("Повернутись");
    menuBar->addAction(createAdminWindowAction);

    connect(createAdminWindowAction, &QAction::triggered, this, &CreateAdminWindow::slotSignalToAdminWindowCloseEvent);
}

void CreateAdminWindow::setDefaultCreateAdminWindowStatus()
{
    const QList<QLineEdit*> lineEdits = CreateAdminWindow::findChildren<QLineEdit*>();
    for (QLineEdit* lineEdit : lineEdits)
    {
        lineEdit->clear();
        lineEdit->clearFocus();
    }

    ui->roleCheckBox->setCheckState(Qt::Unchecked);
    ui->loginLineEdit->setFocus();
    ui->createAdminPushButton->setEnabled(false);
}

void CreateAdminWindow::setLineEditValidator()
{
    myValidator->setLoginLineEditValidator(ui->loginLineEdit);
    myValidator->setPasswordLineEditValidator(ui->passwordLineEdit);
    myValidator->setCyrillicLineEditValidator(ui->lastnameLineEdit, 20);
    myValidator->setCyrillicLineEditValidator(ui->firstnameLineEdit, 15);
    myValidator->setCyrillicLineEditValidator(ui->middlenameLineEdit, 20);
    myValidator->setIntegerLineEditValidator(ui->passportLineEdit, 9);
    ui->telephoneLineEdit->setInputMask("+38\\0 (99) 999 99 99");
    myValidator->setAdressLineEditValidator(ui->adressLineEdit);
}

void CreateAdminWindow::checkLineEditCorrectInput()
{
    if( ui->loginLineEdit->text().isEmpty() ||
        ui->loginLineEdit->text().size() < 6 ||
        ui->passwordLineEdit->text().isEmpty() ||
        ui->passwordLineEdit->text().size() < 8 ||
        ui->lastnameLineEdit->text().isEmpty() ||
        ui->firstnameLineEdit->text().isEmpty() ||
        ui->middlenameLineEdit->text().isEmpty() ||
        ui->passportLineEdit->text().isEmpty() ||
        ui->passportLineEdit->text().size() != 9 ||
        ui->telephoneLineEdit->text().size() != 19 ||
        ui->adressLineEdit->text().isEmpty())
    {
        ui->createAdminPushButton->setEnabled(false);
        return;
    }
    else
    {
        ui->createAdminPushButton->setEnabled(true);
    }
}

Admin CreateAdminWindow::getCreatedAdminData()
{
    Initials initials;
    initials.lastname = ui->lastnameLineEdit->text();
    initials.firstname = ui->firstnameLineEdit->text();
    initials.middlename = ui->middlenameLineEdit->text();

    QString role;
    (ui->roleCheckBox->isChecked()) ? role = "Головний адміністратор" : role = "Адміністратор";

    PersonalAdmin personalAdmin;
    personalAdmin.setPassport(ui->passportLineEdit->text());
    personalAdmin.setTelephone(ui->telephoneLineEdit->text());
    personalAdmin.setAdress(ui->adressLineEdit->text());

    return Admin(ui->loginLineEdit->text(), ui->passwordLineEdit->text(), initials, role, personalAdmin);
}

void CreateAdminWindow::slotSignalToAdminWindowCloseEvent()
{
    sendSignalToAdminWindowCloseEvent();
}

void CreateAdminWindow::on_createAdminPushButton_clicked()
{
    QSqlQuery checkQuery(QSqlDatabase::database("MyDatabase"));

    checkQuery.prepare("SELECT admin_id FROM admin WHERE admin_login = :login");
    checkQuery.bindValue(":login", ui->loginLineEdit->text());
    if (checkQuery.exec() && checkQuery.next())
    {
        QMessageBox::critical(this, "Помилка створення адміністратора", "Адміністратор с таким логіном вже наявний у системі!");
        return;
    }

    checkQuery.prepare("SELECT personaladmin_admin_id FROM personaladmin WHERE personaladmin_passport = :passport");
    checkQuery.bindValue(":passport", ui->passportLineEdit->text());
    if (checkQuery.exec() && checkQuery.next())
    {
        QMessageBox::critical(this, "Помилка створення адміністратора", "Адміністратор с таким номером паспорта вже наявний у системі!");
        return;
    }

    checkQuery.prepare("SELECT personaladmin_admin_id FROM personaladmin WHERE personaladmin_telephone = :telephone");
    checkQuery.bindValue(":telephone", ui->telephoneLineEdit->text());
    if (checkQuery.exec() && checkQuery.next())
    {
        QMessageBox::critical(this, "Помилка створення адміністратора", "Адміністратор с таким номером телефона вже наявний у системі!");
        return;
    }

    sendSignalToAdminWindowPushButtonClicked();
    setDefaultCreateAdminWindowStatus();
}

void CreateAdminWindow::on_loginLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput();
}

void CreateAdminWindow::on_passwordLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput();
}

void CreateAdminWindow::on_lastnameLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput();
}

void CreateAdminWindow::on_firstnameLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput();
}

void CreateAdminWindow::on_middlenameLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput();
}

void CreateAdminWindow::on_passportLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput();
}

void CreateAdminWindow::on_telephoneLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput();
}

void CreateAdminWindow::on_adressLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput();
}

