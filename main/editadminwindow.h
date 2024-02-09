#ifndef EDITADMINWINDOW_H
#define EDITADMINWINDOW_H

#include "admin.h"
#include "myvalidator.h"

#include "headers.h"

namespace Ui {
class EditAdminWindow;
}

class EditAdminWindow : public QMainWindow
{

    Q_OBJECT

public:
    explicit EditAdminWindow(QWidget *parent = nullptr);
    ~EditAdminWindow();

    void closeEvent(QCloseEvent *event);

    void setEditAdminWindowConfig();

    void setDefaultCreateAdminWindowStatus();

    void setLineEditValidator();

    void checkLineEditCorrectInput();

    Admin getEditedAdminData();

signals:
    void sendSignalToAdminWindowCloseEvent();

    void sendSignalToAdminWindowPushButtonClicked();

private slots:
    void slotSignalToAdminWindowCloseEvent();

    void on_editAdminPushButton_clicked();

    void on_loginLineEdit_textEdited(const QString &arg1);

    void on_passwordLineEdit_textEdited(const QString &arg1);

    void on_lastnameLineEdit_textEdited(const QString &arg1);

    void on_firstnameLineEdit_textEdited(const QString &arg1);

    void on_middlenameLineEdit_textEdited(const QString &arg1);

    void on_passportLineEdit_textEdited(const QString &arg1);

    void on_telephoneLineEdit_textEdited(const QString &arg1);

    void on_adressLineEdit_textEdited(const QString &arg1);

private:
    Ui::EditAdminWindow *ui;

    Admin editedAdminData;
    MyValidator *myValidator;

    QMenuBar *menuBar;
    QWidget *parentWidget;

};

#endif
