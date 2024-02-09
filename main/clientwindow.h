#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include "client.h"
#include "clienttableviewaction.h"

#include "personalclient.h"
#include "personalclienttableviewaction.h"

#include "medicaldata.h"
#include "medicaldatatableviewaction.h"

#include "createclientwindow.h"
#include "editclientwindow.h"
#include "resetmedicaldatawindow.h"

#include "headers.h"

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();

    void closeEvent(QCloseEvent *event);

    void setClientWindowConfig();

    void setDefaultClientWindowStatus();

    void setLineEditValidator();

    void checkLineEditCorrectInput();

    void generalLineEditAction();

    void filtersLineEditAction();

    void checkBoxAction();

signals:
    void sendSignalToMainWindowCloseEvent();

    void sendSignalToMainWindowResetClientTableView();

private slots:    
    void slotSignalToMainWindowCloseEvent();

    void getSignalFromCreateClientWindowCloseEvent();

    void getSignalFromCreateClientWindowPushButtonClicked();

    void getSignalFromEditClientWindowCloseEvent();

    void getSignalFromEditClientWindowPushButtonClicked();

    void getSignalFromResetMedicalDataWindowCloseEvent();

    void getSignalFromResetMedicalDataWindowPushButtonClicked();

    void on_createClientPushButton_clicked();

    void on_editClientPushButton_clicked();

    void on_removeClientPushButton_clicked();

    void on_generalLineEdit_textEdited(const QString &arg1);

    void on_lastnameLineEdit_textEdited(const QString &arg1);

    void on_firstnameLineEdit_textEdited(const QString &arg1);

    void on_middlenameLineEdit_textEdited(const QString &arg1);

    void on_maleCheckBox_clicked();

    void on_femaleCheckBox_clicked();

    void on_resetMedicalDataPushButton_clicked();

    void on_clientTableView_clicked(const QModelIndex &index);

private:
    Ui::ClientWindow *ui;

    CreateClientWindow *createClientWindow;
    EditClientWindow *editClientWindow;
    ResetMedicalDataWindow *resetMedicalDataWindow;

    QString gender;

    Client client;
    ClientTableViewAction *clientTableViewAction;

    PersonalClient personalClient;
    PersonalClientTableViewAction *personalClientTableViewAction;

    MedicalData medicalData;
    MedicalDataTableViewAction *medicalDataTableViewAction;

    QMenuBar *menuBar;
    QWidget  *parentWidget;

    MyValidator *myValidator;
};

#endif
