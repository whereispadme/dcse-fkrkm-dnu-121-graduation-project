#include "editadminwindow.h"
#include "ui_editadminwindow.h"

EditAdminWindow::EditAdminWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::EditAdminWindow)
{
    ui->setupUi(this);

    parentWidget = new QWidget();

    setEditAdminWindowConfig();
    setDefaultCreateAdminWindowStatus();
    setLineEditValidator();
}

EditAdminWindow::~EditAdminWindow()
{
    delete ui;
    delete myValidator;
    delete menuBar;
    delete parentWidget;
}

void EditAdminWindow::closeEvent(QCloseEvent *event)
{
    sendSignalToAdminWindowCloseEvent();
}

void EditAdminWindow::setEditAdminWindowConfig()
{
    setWindowTitle("Редагувати адміністратора");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    menuBar = new QMenuBar();
    setMenuBar(menuBar);

    QAction *EditAdminWindowAction = new QAction("Повернутись");
    menuBar->addAction(EditAdminWindowAction);

    connect(EditAdminWindowAction, &QAction::triggered, this, &EditAdminWindow::slotSignalToAdminWindowCloseEvent);
}

void EditAdminWindow::setDefaultCreateAdminWindowStatus()
{
    const QList<QLineEdit*> lineEdits = EditAdminWindow::findChildren<QLineEdit*>();
    for (QLineEdit* lineEdit : lineEdits)
    {
        lineEdit->clear();
        lineEdit->clearFocus();
    }

    ui->roleCheckBox->setCheckState(Qt::Unchecked);
    ui->loginLineEdit->setFocus();
    ui->editAdminPushButton->setEnabled(false);
}

void EditAdminWindow::setLineEditValidator()
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

void EditAdminWindow::checkLineEditCorrectInput()
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
        ui->editAdminPushButton->setEnabled(false);
        return;
    }
    else
    {
        ui->editAdminPushButton->setEnabled(true);
    }
}

Admin EditAdminWindow::getEditedAdminData()
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

void EditAdminWindow::slotSignalToAdminWindowCloseEvent()
{
    sendSignalToAdminWindowCloseEvent();
}

void EditAdminWindow::on_editAdminPushButton_clicked()
{
    QSqlQuery checkQuery(QSqlDatabase::database("MyDatabase"));

    checkQuery.prepare("SELECT admin_id FROM admin WHERE admin_login = :login");
    checkQuery.bindValue(":login", ui->loginLineEdit->text());
    if (checkQuery.exec() && checkQuery.next())
    {
        QMessageBox::critical(this, "Помилка редагування адміністратора", "Адміністратор с таким логіном вже наявний у системі!");
        return;
    }

    checkQuery.prepare("SELECT personaladmin_admin_id FROM personaladmin WHERE personaladmin_passport = :passport");
    checkQuery.bindValue(":passport", ui->passportLineEdit->text());
    if (checkQuery.exec() && checkQuery.next())
    {
        QMessageBox::critical(this, "Помилка редагування адміністратора", "Адміністратор с таким номером паспорта вже наявний у системі!");
        return;
    }

    checkQuery.prepare("SELECT personaladmin_admin_id FROM personaladmin WHERE personaladmin_telephone = :telephone");
    checkQuery.bindValue(":telephone", ui->telephoneLineEdit->text());
    if (checkQuery.exec() && checkQuery.next())
    {
        QMessageBox::critical(this, "Помилка редагування адміністратора", "Адміністратор с таким номером телефона вже наявний у системі!");
        return;
    }

    sendSignalToAdminWindowPushButtonClicked();
}

void EditAdminWindow::on_loginLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput();
}

void EditAdminWindow::on_passwordLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput();
}

void EditAdminWindow::on_lastnameLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput();
}

void EditAdminWindow::on_firstnameLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput();
}

void EditAdminWindow::on_middlenameLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput();
}

void EditAdminWindow::on_passportLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput();
}

void EditAdminWindow::on_telephoneLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput();
}

void EditAdminWindow::on_adressLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput();
}

