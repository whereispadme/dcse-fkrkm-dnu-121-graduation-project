#ifndef EDITSUBSCRIPTIONWINDOW_H
#define EDITSUBSCRIPTIONWINDOW_H

#include "subscription.h"
#include "myvalidator.h"

#include "headers.h"

namespace Ui {
class EditSubscriptionWindow;
}

class EditSubscriptionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditSubscriptionWindow(QWidget *parent = nullptr);
    ~EditSubscriptionWindow();

    void closeEvent(QCloseEvent *event);

    void setEditSubscriptionWindowWindowConfig();

    void setDefaultEditSubscriptionWindowStatus();

    void setLineEditValidator();

    Subscription getEditedSubscriptionData();

signals:
    void sendSignalToSubscriptionWindowCloseEvent();

    void sendSignalToSubscriptionWindowPushButtonClicked();

private slots:
    void slotSignalToSubscriptionWindowCloseEvent();

    void on_editSubscriptionPushButton_clicked();

    void on_unlimitedRadioButton_clicked();

    void on_limitedRadioButton_clicked();

private:
    Ui::EditSubscriptionWindow *ui;

    Subscription editedSubscriptionData;
    MyValidator *myValidator;

    QMenuBar *menuBar;
    QWidget *parentWidget;

};

#endif

