#ifndef CREATESUBSCRIPTIONWINDOW_H
#define CREATESUBSCRIPTIONWINDOW_H

#include "subscription.h"
#include "myvalidator.h"

#include "headers.h"

namespace Ui {
class CreateSubscriptionWindow;
}

class CreateSubscriptionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateSubscriptionWindow(QWidget *parent = nullptr);
    ~CreateSubscriptionWindow();

    void closeEvent(QCloseEvent *event);

    void setCreateSubscriptionWindowWindowConfig();

    void setDefaultCreateSubscriptionWindowStatus();

    void setLineEditValidator();

    Subscription getCreatedSubscriptionData();

signals:
    void sendSignalToSubscriptionWindowCloseEvent();

    void sendSignalToSubscriptionWindowPushButtonClicked();

private slots:
    void slotSignalToSubscriptionWindowCloseEvent();

    void on_createSubscriptionPushButton_clicked();

    void on_unlimitedRadioButton_clicked();

    void on_limitedRadioButton_clicked();

private:
    Ui::CreateSubscriptionWindow *ui;

    Subscription createdSubscriptionData;
    MyValidator *myValidator;

    QMenuBar *menuBar;
    QWidget *parentWidget;

};

#endif
