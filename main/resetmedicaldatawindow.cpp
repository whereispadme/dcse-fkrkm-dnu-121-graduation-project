#include "resetmedicaldatawindow.h"
#include "ui_resetmedicaldatawindow.h"

ResetMedicalDataWindow::ResetMedicalDataWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::ResetMedicalDataWindow)
{
    ui->setupUi(this);

    parentWidget = new QWidget();

    setResetMedicalDataWindowConfig();
    setDefaultResetMedicalDataWindowStatus();
    setLineEditValidator();
}

ResetMedicalDataWindow::~ResetMedicalDataWindow()
{
    delete ui;
    delete myValidator;
    delete menuBar;
    delete parentWidget;
}

void ResetMedicalDataWindow::closeEvent(QCloseEvent *event)
{
    sendSignalToClientWindowCloseEvent();
}

void ResetMedicalDataWindow::setResetMedicalDataWindowConfig()
{
    setWindowTitle("Оновити медичну довідку");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    menuBar = new QMenuBar();
    setMenuBar(menuBar);

    QAction *resetMedicalDataWindowAction = new QAction("Повернутись");
    menuBar->addAction(resetMedicalDataWindowAction);

    connect(resetMedicalDataWindowAction, &QAction::triggered, this, &ResetMedicalDataWindow::slotSignalToClientWindowCloseEvent);
}

void ResetMedicalDataWindow::setDefaultResetMedicalDataWindowStatus()
{
    const QList<QLineEdit*> lineEdits = ResetMedicalDataWindow::findChildren<QLineEdit*>();
    for (QLineEdit* lineEdit : lineEdits)
    {
        lineEdit->clear();
        lineEdit->clearFocus();
    }

    QDate currentDate = QDate::currentDate();
    ui->startDateEdit->setDate(currentDate);
    ui->endDateEdit->setDate(currentDate);

    ui->applyPushButton->setEnabled(false);
}

void ResetMedicalDataWindow::setLineEditValidator()
{
    myValidator->setAdressLineEditValidator(ui->institutionLineEdit);
    myValidator->setAdressLineEditValidator(ui->doctorLineEdit);
    myValidator->setAdressLineEditValidator(ui->decisionLineEdit);
}

void ResetMedicalDataWindow::checkLineEditCorrectInput()
{
    if( ui->institutionLineEdit->text().isEmpty() ||
        ui->doctorLineEdit->text().isEmpty() ||
        ui->decisionLineEdit->text().isEmpty())
    {
        ui->applyPushButton->setEnabled(false);
        return;
    }
    else
    {
        ui->applyPushButton->setEnabled(true);
    }
}

MedicalData ResetMedicalDataWindow::getEditedMedicalData()
{
    medicalData.setInstitution(ui->institutionLineEdit->text());
    medicalData.setDoctor(ui->doctorLineEdit->text());
    medicalData.setDateissue(ui->startDateEdit->text());
    medicalData.setDateexpiration(ui->endDateEdit->text());
    medicalData.setDecision(ui->decisionLineEdit->text());

    return medicalData;
}

void ResetMedicalDataWindow::slotSignalToClientWindowCloseEvent()
{
    sendSignalToClientWindowCloseEvent();
}

void ResetMedicalDataWindow::on_applyPushButton_clicked()
{
    sendSignalToClientWindowPushButtonClicked();
}

void ResetMedicalDataWindow::on_institutionLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput();
}

void ResetMedicalDataWindow::on_doctorLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput();
}

void ResetMedicalDataWindow::on_decisionLineEdit_textEdited(const QString &arg1)
{
    checkLineEditCorrectInput();
}

