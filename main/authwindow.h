#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include "headers.h"
#include "myvalidator.h"

namespace Ui {
class AuthWindow;
}

class AuthWindow : public QWidget
{

    Q_OBJECT

public:
    explicit AuthWindow(QWidget *parent = nullptr);
    ~AuthWindow();

    void closeEvent(QCloseEvent *event);
    void setAuthWindowConfiguration();
    void checkAuthorizationCorrectInput();

    QString getCurrentLogin();
    QString getCurrentPassword();

signals:
    void sendSignalToMainWindowApplyPushButtonClicked();

private slots:
    void on_loginLineEdit_textEdited(const QString &arg1);

    void on_passwordLineEdit_textEdited(const QString &arg1);

    void on_hiddenvisibleCheckBox_stateChanged(int arg1);

    void on_visibleIconPushButton_clicked();

    void on_hiddenIconPushButton_clicked();

    void on_applyPushButton_clicked();

private:
    Ui::AuthWindow *ui;

    QString currentLogin;
    QString currentPassword;

    MyValidator *myValidator;

};

#endif
