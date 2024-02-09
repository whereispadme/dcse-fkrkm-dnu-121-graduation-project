#ifndef REPORTWINDOW_H
#define REPORTWINDOW_H

#include "myvalidator.h"
#include "headers.h"

namespace Ui {
class ReportWindow;
}

class ReportWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReportWindow(QWidget *parent = nullptr);
    ~ReportWindow();

    void closeEvent(QCloseEvent *event);

    void setReportWindowConfig();

    void setDefaultReportWindowStatus();

signals:
    void sendSignalToMainWindowCloseEvent();

private slots:
    void slotSignalToMainWindowCloseEvent();

    void on_pushButton_clicked();

private:
    Ui::ReportWindow *ui;

    QBarSeries *series;
    QChart *chart;
    QBarCategoryAxis *axisX;
    QValueAxis *axisY;
    QChartView *chartView;
    QHBoxLayout *layout;

    QMenuBar *menuBar;
    QWidget *parentWidget;

    MyValidator *myValidator;

};

#endif
