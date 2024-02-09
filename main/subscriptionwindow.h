#ifndef SUBSCRIPTIONWINDOW_H
#define SUBSCRIPTIONWINDOW_H

#include "subscription.h"
#include "subscriptiontableviewaction.h"

#include "createsubscriptionwindow.h"
#include "editsubscriptionwindow.h"

#include "subscriptionclient.h"
#include "subscriptionclienttableviewaction.h"

#include "headers.h"

namespace Ui {
class SubscriptionWindow;
}

class SubscriptionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SubscriptionWindow(QWidget *parent = nullptr);
    ~SubscriptionWindow();

    void closeEvent(QCloseEvent *event);

    void setSubscriptionWindowConfig();

    void setDefaultSubscriptionWindowStatus();

    void setLineEditValidator();

    void checkLineEditCorrectInput();

    void checkClearLineEditForResetTableView();

    void generalLineEditAction();

    void filtersLineEditAction();

    void checkBoxAction();

signals:
    void sendSignalToMainWindowCloseEvent();

    void sendSignalToMainWindowResetTableView();

private slots:
    void slotSignalToMainWindowCloseEvent();

    void getSignalFromCreateSubscriptionWindowCloseEvent();

    void getSignalFromCreateSubscriptionWindowPushButtonClicked();

    void getSignalFromEditSubscriptionWindowCloseEvent();

    void getSignalFromEditSubscriptionWindowPushButtonClicked();

    void on_generalLineEdit_textEdited(const QString &arg1);

    void on_titleLineEdit_textEdited(const QString &arg1);

    void on_trainingAmountLineEdit_textEdited(const QString &arg1);

    void on_priceLineEdit_textEdited(const QString &arg1);

    void on_unlimitedCheckBox_stateChanged(int arg1);

    void on_createSubPushButton_clicked();

    void on_editSubPushButton_clicked();

    void on_removeSubPushButton_clicked();

    void on_limitedCheckBox_stateChanged(int arg1);

    void on_subscriptionTableView_clicked(const QModelIndex &index);

private:
    Ui::SubscriptionWindow *ui;

    CreateSubscriptionWindow *createSubscriptionWindow;
    EditSubscriptionWindow *editSubscriptionWindow;

    Subscription subscription;
    SubscriptionTableViewAction *subscriptionTableViewAction;

    Subscription subscriptionclient;
    SubscriptionClientTableViewAction *subscriptionclientTableViewAction;

    QMenuBar *menuBar;
    QWidget *parentWidget;

    MyValidator *myValidator;
};

#endif
