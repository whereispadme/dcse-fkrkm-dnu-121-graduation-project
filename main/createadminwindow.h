#ifndef CREATEADMINWINDOW_H
#define CREATEADMINWINDOW_H

#include "admin.h"
#include "myvalidator.h"

#include "headers.h"

namespace Ui {
class CreateAdminWindow;
}

class CreateAdminWindow : public QMainWindow
{

    Q_OBJECT

public:
    explicit CreateAdminWindow(QWidget *parent = nullptr);
    ~CreateAdminWindow();

    void closeEvent(QCloseEvent *event);

    void setCreateAdminWindowConfig();

    void setDefaultCreateAdminWindowStatus();

    void setLineEditValidator();

    void checkLineEditCorrectInput();

    Admin getCreatedAdminData();

signals:
    void sendSignalToAdminWindowCloseEvent();

    void sendSignalToAdminWindowPushButtonClicked();

private slots:
    void slotSignalToAdminWindowCloseEvent();

    void on_createAdminPushButton_clicked();

    void on_loginLineEdit_textEdited(const QString &arg1);

    void on_passwordLineEdit_textEdited(const QString &arg1);

    void on_lastnameLineEdit_textEdited(const QString &arg1);

    void on_firstnameLineEdit_textEdited(const QString &arg1);

    void on_middlenameLineEdit_textEdited(const QString &arg1);

    void on_passportLineEdit_textEdited(const QString &arg1);

    void on_telephoneLineEdit_textEdited(const QString &arg1);

    void on_adressLineEdit_textEdited(const QString &arg1);

private:
    Ui::CreateAdminWindow *ui;

    Admin createdAdminData;
    MyValidator *myValidator;

    QMenuBar *menuBar;
    QWidget *parentWidget;

};

#endif
