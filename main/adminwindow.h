#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include "admin.h"
#include "admintableviewaction.h"

#include "personaladmin.h"
#include "personaladmintableviewaction.h"

#include "createadminwindow.h"
#include "editadminwindow.h"

#include "headers.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

    void closeEvent(QCloseEvent *event);

    void setAdminWindowConfig();

    void setDefaultAdminWindowStatus();

    void setLineEditValidator();

    void checkLineEditCorrectInput();

    void generalLineEditAction();

    void filtersLineEditAction();

    void checkBoxAction();

    void setCurrentAdminLogin(QString);

signals:
    void sendSignalToMainWindowCloseEvent();

    void sendSignalToEditAdminWindow(Admin admin);

private slots:
    void slotSignalToMainWindowCloseEvent();

    void getSignalFromCreateAdminWindowCloseEvent();

    void getSignalFromCreateAdminWindowPushButtonClicked();

    void getSignalFromEditAdminWindowCloseEvent();

    void getSignalFromEditAdminWindowPushButtonClicked();

    void on_generalLineEdit_textEdited(const QString &arg1);

    void on_loginLineEdit_textEdited(const QString &arg1);

    void on_lastnameLineEdit_textEdited(const QString &arg1);

    void on_firstnameLineEdit_textEdited(const QString &arg1);

    void on_middlenameLineEdit_textEdited(const QString &arg1);

    void on_createAdminPushButton_clicked();

    void on_editAdminPushButton_clicked();

    void on_removeAdminPushButton_clicked();

    void on_mainadminCheckBox_clicked();

    void on_adminCheckBox_clicked();

    void on_adminTableView_clicked(const QModelIndex &index);

private:
    Ui::AdminWindow *ui;

    CreateAdminWindow *createAdminWindow;
    EditAdminWindow *editAdminWindow;

    QString role;

    Admin admin;
    AdminTableViewAction *adminTableViewAction;

    PersonalAdmin personalAdmin;
    PersonalAdminTableViewAction *personalAdminTableViewAction;

    QMenuBar *menuBar;
    QWidget *parentWidget;

    MyValidator *myValidator;

    QString currentAdminLogin;

};

#endif
