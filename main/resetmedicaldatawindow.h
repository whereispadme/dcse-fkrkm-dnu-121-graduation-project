#ifndef RESETMEDICALDATAWINDOW_H
#define RESETMEDICALDATAWINDOW_H

#include "medicaldata.h"
#include "myvalidator.h"

#include "headers.h"

namespace Ui {
class ResetMedicalDataWindow;
}

class ResetMedicalDataWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ResetMedicalDataWindow(QWidget *parent = nullptr);
    ~ResetMedicalDataWindow();

    void closeEvent(QCloseEvent *event);

    void setResetMedicalDataWindowConfig();

    void setDefaultResetMedicalDataWindowStatus();

    void setLineEditValidator();

    void checkLineEditCorrectInput();

    MedicalData getEditedMedicalData();

signals:
    void sendSignalToClientWindowCloseEvent();

    void sendSignalToClientWindowPushButtonClicked();

private slots:
    void slotSignalToClientWindowCloseEvent();

    void on_applyPushButton_clicked();

    void on_institutionLineEdit_textEdited(const QString &arg1);

    void on_doctorLineEdit_textEdited(const QString &arg1);

    void on_decisionLineEdit_textEdited(const QString &arg1);

private:
    Ui::ResetMedicalDataWindow *ui;

    MedicalData medicalData;
    MyValidator *myValidator;

    QMenuBar *menuBar;
    QWidget *parentWidget;

};

#endif
