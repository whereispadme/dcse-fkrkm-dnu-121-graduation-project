#include "editclientwindow.h"
#include "ui_editclientwindow.h"

EditClientWindow::EditClientWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::EditClientWindow)
{
    ui->setupUi(this);

    parentWidget = new QWidget();

    setEditClientWindowConfig();
    setDefaultEditClientWindowStatus();
    setLineEditValidator();
}

EditClientWindow::~EditClientWindow()
{
    delete ui;
    delete myValidator;
    delete menuBar;
    delete parentWidget;
}

void EditClientWindow::closeEvent(QCloseEvent *event)
{
    sendSignalToClientWindowCloseEvent();
}

void EditClientWindow::setEditClientWindowConfig()
{
    setWindowTitle("Редагувати клієнта");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    menuBar = new QMenuBar();
    setMenuBar(menuBar);

    QAction *EditClientWindowAction = new QAction("Повернутись");
    menuBar->addAction(EditClientWindowAction);

    connect(EditClientWindowAction, &QAction::triggered, this, &EditClientWindow::slotSignalToClientWindowCloseEvent);
}

void EditClientWindow::setDefaultEditClientWindowStatus()
{
    const QList<QLineEdit*> lineEdits = EditClientWindow::findChildren<QLineEdit*>();
    for (QLineEdit* lineEdit : lineEdits)
    {
        lineEdit->clear();
        lineEdit->clearFocus();
    }

    ui->maleRadioButton->setChecked(true);
}

void EditClientWindow::setLineEditValidator()
{
    myValidator->setCyrillicLineEditValidator(ui->lastnameLineEdit, 20);
    myValidator->setCyrillicLineEditValidator(ui->firstnameLineEdit, 15);
    myValidator->setCyrillicLineEditValidator(ui->middlenameLineEdit, 20);
    myValidator->setIntegerLineEditValidator(ui->passportLineEdit, 9);
    ui->telephoneLineEdit->setInputMask("+38\\0 (99) 999 99 99");
}

Client EditClientWindow::getEditedClientData()
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

    return Client(initials, gender, personalClient, MedicalData());
}

void EditClientWindow::slotSignalToClientWindowCloseEvent()
{
    sendSignalToClientWindowCloseEvent();
}

void EditClientWindow::on_editClientPushButton_clicked()
{
    sendSignalToClientWindowPushButtonClicked();
}

