#include "editsubscriptionwindow.h"
#include "ui_editsubscriptionwindow.h"

EditSubscriptionWindow::EditSubscriptionWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::EditSubscriptionWindow)
{
    ui->setupUi(this);

    parentWidget = new QWidget();

    setEditSubscriptionWindowWindowConfig();
    setDefaultEditSubscriptionWindowStatus();
    setLineEditValidator();
}

EditSubscriptionWindow::~EditSubscriptionWindow()
{
    delete ui;
    delete myValidator;
    delete menuBar;
    delete parentWidget;
}

void EditSubscriptionWindow::closeEvent(QCloseEvent *event)
{
    sendSignalToSubscriptionWindowCloseEvent();
}

void EditSubscriptionWindow::setEditSubscriptionWindowWindowConfig()
{
    setWindowTitle("Редагувати абонемент");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    menuBar = new QMenuBar();
    setMenuBar(menuBar);

    QAction *CreateClientWindowAction = new QAction("Повернутись");
    menuBar->addAction(CreateClientWindowAction);

    connect(CreateClientWindowAction, &QAction::triggered, this, &EditSubscriptionWindow::slotSignalToSubscriptionWindowCloseEvent);
}

void EditSubscriptionWindow::setDefaultEditSubscriptionWindowStatus()
{
    const QList<QLineEdit*> lineEdits = EditSubscriptionWindow::findChildren<QLineEdit*>();
    for (QLineEdit* lineEdit : lineEdits)
    {
        lineEdit->clear();
        lineEdit->clearFocus();
    }

    ui->limitedRadioButton->setChecked(true);
    ui->trainingAmountLineEdit->setEnabled(true);
}

void EditSubscriptionWindow::setLineEditValidator()
{
    myValidator->setAdressLineEditValidator(ui->titleLineEdit);
    myValidator->setIntegerLineEditValidator(ui->trainingAmountLineEdit, 2);
    myValidator->setIntegerLineEditValidator(ui->priceLineEdit, 4);
}

Subscription EditSubscriptionWindow::getEditedSubscriptionData()
{

    QString type;
    QString days;

    (ui->unlimitedRadioButton->isChecked()) ? type = "Безлімітний" : type = "Обмежений";

    QStringList checkedItems;
    QList<QCheckBox *> checkBoxes = EditSubscriptionWindow::findChildren<QCheckBox *>();

    for (QCheckBox *checkBox : checkBoxes) {
        if (checkBox->isChecked())
        {
            if(checkBox->text() == "Понеділок")
                checkedItems.append("Пн ");

            if(checkBox->text() == "Вівторок")
                checkedItems.append(" Вт ");

            if(checkBox->text() == "Середа")
                checkedItems.append(" Ср ");

            if(checkBox->text() == "Четвер")
                checkedItems.append(" Чт ");

            if(checkBox->text() == "П'ятниця")
                checkedItems.append(" Пт ");

            if(checkBox->text() == "Субота")
                checkedItems.append(" Сб ");

            if(checkBox->text() == "Неділя")
                checkedItems.append(" Нд ");
        }
    }

    days = checkedItems.join("");

    return Subscription(ui->titleLineEdit->text(), type, ui->timeEdit->text(), ui->timeEdit_2->text(), ui->trainingAmountLineEdit->text(), days, ui->priceLineEdit->text());
}

void EditSubscriptionWindow::slotSignalToSubscriptionWindowCloseEvent()
{
    sendSignalToSubscriptionWindowCloseEvent();
}

void EditSubscriptionWindow::on_editSubscriptionPushButton_clicked()
{
    sendSignalToSubscriptionWindowPushButtonClicked();
}

void EditSubscriptionWindow::on_unlimitedRadioButton_clicked()
{
    ui->trainingAmountLineEdit->setEnabled(false);
}

void EditSubscriptionWindow::on_limitedRadioButton_clicked()
{
    ui->trainingAmountLineEdit->setEnabled(true);
}

