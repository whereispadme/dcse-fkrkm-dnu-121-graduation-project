#ifndef CREATECLIENTWINDOW_H
#define CREATECLIENTWINDOW_H

#include "client.h"
#include "myvalidator.h"

#include "headers.h"

namespace Ui {
class CreateClientWindow;
}

class CreateClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateClientWindow(QWidget *parent = nullptr);
    ~CreateClientWindow();

    void closeEvent(QCloseEvent *event);

    void setCreateClientWindowConfig();

    void setDefaultCreateClientWindowStatus();

    void setLineEditValidator();

    void checkLineEditCorrectInput(int);

    Client getCreatedClientData();

signals:
    void sendSignalToClientWindowCloseEvent();

    void sendSignalToClientWindowPushButtonClicked();

private slots:
    void slotSignalToClientWindowCloseEvent();

    void on_createClientPushButton_clicked();

    void on_applyPushButton_clicked();

    void on_lastnameLineEdit_textEdited(const QString &arg1);

    void on_firstnameLineEdit_textEdited(const QString &arg1);

    void on_middlenameLineEdit_textEdited(const QString &arg1);

    void on_passportLineEdit_textEdited(const QString &arg1);

    void on_telephoneLineEdit_textEdited(const QString &arg1);

    void on_institutionLineEdit_textEdited(const QString &arg1);

    void on_doctorLineEdit_textEdited(const QString &arg1);

    void on_decisionLineEdit_textEdited(const QString &arg1);

private:
    Ui::CreateClientWindow *ui;

    Client createdClientData;
    MyValidator *myValidator;

    QMenuBar *menuBar;
    QWidget *parentWidget;

};

#endif
