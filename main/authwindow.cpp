#include "authwindow.h"
#include "ui_authwindow.h"

AuthWindow::AuthWindow(QWidget *parent) : QWidget(parent), ui(new Ui::AuthWindow)
{
    ui->setupUi(this);
    myValidator = new MyValidator;

    setAuthWindowConfiguration();
}

AuthWindow::~AuthWindow()
{
    delete ui;
    delete myValidator;
}

void AuthWindow::closeEvent(QCloseEvent *event)
{
    QApplication::exit();
}

void AuthWindow::setAuthWindowConfiguration()
{
    this->setWindowTitle("Авторизація");
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::Window | Qt::WindowCloseButtonHint);

    myValidator->setLoginLineEditValidator(ui->loginLineEdit);
    myValidator->setPasswordLineEditValidator(ui->passwordLineEdit);

    ui->loginLineEdit->clear();
    ui->passwordLineEdit->clear();
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);

    ui->applyPushButton->setEnabled(false);

    ui->visibleIconPushButton->setIcon(QIcon(":/icons/visible.png"));
    ui->hiddenIconPushButton->setIcon(QIcon(":/icons/hidden.png"));

    ui->visibleIconPushButton->show();
    ui->hiddenIconPushButton->hide();

    ui->loginLineEdit->setFocus();
}

void AuthWindow::checkAuthorizationCorrectInput()
{
    if(ui->loginLineEdit->text().isEmpty() || ui->passwordLineEdit->text().isEmpty())
    {
        ui->applyPushButton->setEnabled(false);
        return;
    }
    else
    {
        ui->applyPushButton->setEnabled(true);
    }

    if((ui->loginLineEdit->text().size() <= 5 || ui->loginLineEdit->text().size() >= 21) || (ui->passwordLineEdit->text().size() <= 7 || ui->passwordLineEdit->text().size() >= 21))
    {
        ui->applyPushButton->setEnabled(false);
        return;
    }
    else
    {
        ui->applyPushButton->setEnabled(true);
    }
}

QString AuthWindow::getCurrentLogin()
{
    return this->currentLogin;
}

QString AuthWindow::getCurrentPassword()
{
    return this->currentPassword;
}

void AuthWindow::on_loginLineEdit_textEdited(const QString &arg1)
{
    checkAuthorizationCorrectInput();
    this->currentLogin = arg1;
}

void AuthWindow::on_passwordLineEdit_textEdited(const QString &arg1)
{
    checkAuthorizationCorrectInput();
    this->currentPassword = arg1;
}

void AuthWindow::on_visibleIconPushButton_clicked()
{
    ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
    ui->visibleIconPushButton->hide();
    ui->hiddenIconPushButton->show();
    
    ui->hiddenvisibleCheckBox->setChecked(true);
    ui->passwordLineEdit->setFocus();
}

void AuthWindow::on_hiddenIconPushButton_clicked()
{
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->hiddenIconPushButton->hide();
    ui->visibleIconPushButton->show();
    
    ui->hiddenvisibleCheckBox->setChecked(false);
    ui->passwordLineEdit->setFocus();
}

void AuthWindow::on_applyPushButton_clicked()
{
    emit sendSignalToMainWindowApplyPushButtonClicked();
}

void AuthWindow::on_hiddenvisibleCheckBox_stateChanged(int arg1)
{
    if(ui->hiddenvisibleCheckBox->isChecked())
    {
        ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
        ui->visibleIconPushButton->hide();
        ui->hiddenIconPushButton->show();
    }
    else
    {
        ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
        ui->visibleIconPushButton->show();
        ui->hiddenIconPushButton->hide();
    }
}
