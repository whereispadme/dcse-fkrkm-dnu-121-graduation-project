#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "authwindow.h"
#include "clientwindow.h"
#include "subscriptionwindow.h"
#include "adminwindow.h"
#include "reportwindow.h"

#include "clienttableviewaction.h"
#include "subscriptiontableviewaction.h"

#include "headers.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{

    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool setDatabaseConnect();

    void setMainWindowConfig();

    void setMainWindowMenu();

    void setDefaultMainWindowStatus();

    void setLineEditValidator();

private slots:
    void showClientWindow();

    void showSubscriptionWindow();

    void showAdminWindow();

    void showReportWindow();

    void getSignalFromAuthWindowApplyPushButtonClicked();

    void getSignalFromClientWindowCloseEvent();

    void getSignalFromClientWindowResetClientTableView();

    void getSignalFromSubscriptionWindowCloseEvent();

    void getSignalFromSubscriptionWindowResetTableView();

    void getSignalFromAdminWindowCloseEvent();

    void getSignalFromReportWindowCloseEvent();

    void on_createClientPushButton_clicked();

    //tab_1
    void on_subclientGeneralClientLineEdit_textEdited(const QString &arg1);

    void on_subclientGeneralSubscriptionLineEdit_textEdited(const QString &arg1);

    void on_subclientApplyPushButton_clicked();

    //tab_2

    void on_createclientApplyPushButton_clicked();

    void on_checkPushButton_clicked();

    void on_checkGeneralLineEdit_textEdited(const QString &arg1);

    void on_fastSearchGeneralLineEdit_textEdited(const QString &arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_medicaldataApplyPushButton_clicked();

    void on_applyPushButton_clicked();

private:
    Ui::MainWindow *ui;

    AuthWindow *authWindow;
    ClientWindow *clientWindow;
    SubscriptionWindow *subscriptionWindow;
    AdminWindow *adminWindow;
    ReportWindow *reportWindow;

    ClientTableViewAction *subclientClientTableView;
    ClientTableViewAction *clientTableViewAction2;
    ClientTableViewAction *clientTableViewAction3;
    ClientTableViewAction *clientTableViewAction4;

    ClientTableViewAction *fastSearchClientTableViewAction;
    SubscriptionTableViewAction *fastSearchSubscriptionTableViewAction;
    SubscriptionClientTableViewAction *fastSearchSubscriptionClientTableViewAction;

    SubscriptionTableViewAction *subclientSubscriptionTableViewAction;

    Admin currentAdmin;

    QWidget *parentWidget;

    QSqlDatabase database;

    MyValidator *myValidator;
};
#endif
