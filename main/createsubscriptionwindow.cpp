#include "createsubscriptionwindow.h"
#include "ui_createsubscriptionwindow.h"

CreateSubscriptionWindow::CreateSubscriptionWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::CreateSubscriptionWindow)
{
    ui->setupUi(this);

    parentWidget = new QWidget();

    setCreateSubscriptionWindowWindowConfig();
    setDefaultCreateSubscriptionWindowStatus();
    setLineEditValidator();
}

CreateSubscriptionWindow::~CreateSubscriptionWindow()
{
    delete ui;
    delete myValidator;
    delete menuBar;
    delete parentWidget;
}

void CreateSubscriptionWindow::closeEvent(QCloseEvent *event)
{
    sendSignalToSubscriptionWindowCloseEvent();
}

void CreateSubscriptionWindow::setCreateSubscriptionWindowWindowConfig()
{
    setWindowTitle("Створити абонемент");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    menuBar = new QMenuBar();
    setMenuBar(menuBar);

    QAction *CreateClientWindowAction = new QAction("Повернутись");
    menuBar->addAction(CreateClientWindowAction);

    connect(CreateClientWindowAction, &QAction::triggered, this, &CreateSubscriptionWindow::slotSignalToSubscriptionWindowCloseEvent);
}

void CreateSubscriptionWindow::setDefaultCreateSubscriptionWindowStatus()
{
    const QList<QLineEdit*> lineEdits = CreateSubscriptionWindow::findChildren<QLineEdit*>();
    for (QLineEdit* lineEdit : lineEdits)
    {
        lineEdit->clear();
        lineEdit->clearFocus();
    }

    ui->limitedRadioButton->setChecked(true);
    ui->trainingAmountLineEdit->setEnabled(true);
}

void CreateSubscriptionWindow::setLineEditValidator()
{
    myValidator->setAdressLineEditValidator(ui->titleLineEdit);
    myValidator->setIntegerLineEditValidator(ui->trainingAmountLineEdit, 2);
    myValidator->setIntegerLineEditValidator(ui->priceLineEdit, 4);
}

Subscription CreateSubscriptionWindow::getCreatedSubscriptionData()
{
    QString type;
    QString days;

    (ui->unlimitedRadioButton->isChecked()) ? type = "Безлімітний" : type = "Обмежений";

    QStringList checkedItems;
    QList<QCheckBox *> checkBoxes = CreateSubscriptionWindow::findChildren<QCheckBox *>();

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

void CreateSubscriptionWindow::slotSignalToSubscriptionWindowCloseEvent()
{
    sendSignalToSubscriptionWindowCloseEvent();
}

void CreateSubscriptionWindow::on_createSubscriptionPushButton_clicked()
{
    QSqlQuery query(QSqlDatabase::database("MyDatabase"));
    query.prepare("SELECT COUNT(*) FROM subscription WHERE subscription_title = :title");
    query.bindValue(":title", ui->titleLineEdit->text());

    if (query.exec() && query.next())
    {
        int count = query.value(0).toInt();

        // Проверка количества записей с указанным названием абонемента
        if (count > 0)
        {
            // Вывод сообщения о невозможности добавления абонемента с таким же названием
            QMessageBox::critical(this, "Помилка додавання абонемента", "Абонемент з такою назвою вже існує!");
            return;
        }
    }

    sendSignalToSubscriptionWindowPushButtonClicked();
}

void CreateSubscriptionWindow::on_unlimitedRadioButton_clicked()
{
    ui->trainingAmountLineEdit->setEnabled(false);
}

void CreateSubscriptionWindow::on_limitedRadioButton_clicked()
{
    ui->trainingAmountLineEdit->setEnabled(true);
}

