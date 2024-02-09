#ifndef EDITCLIENTWINDOW_H
#define EDITCLIENTWINDOW_H

#include "client.h"
#include "myvalidator.h"

#include "headers.h"

namespace Ui {
class EditClientWindow;
}

class EditClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditClientWindow(QWidget *parent = nullptr);
    ~EditClientWindow();

    void closeEvent(QCloseEvent *event);

    void setEditClientWindowConfig();

    void setDefaultEditClientWindowStatus();

    void setLineEditValidator();

    Client getEditedClientData();

signals:
    void sendSignalToClientWindowCloseEvent();

    void sendSignalToClientWindowPushButtonClicked();

private slots:
    void slotSignalToClientWindowCloseEvent();

    void on_editClientPushButton_clicked();

private:
    Ui::EditClientWindow *ui;

    Client createdClientData;
    MyValidator *myValidator;

    QMenuBar *menuBar;
    QWidget *parentWidget;

};

#endif
