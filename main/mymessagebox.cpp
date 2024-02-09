#include "mymessagebox.h"

MyMessageBox::MyMessageBox()
{

}

MyMessageBox::~MyMessageBox()
{

}

void MyMessageBox::setQMessageBoxInformation(QString titleText, QString infoText, QIcon windowIcon)
{

    QMessageBox msgBox;
    msgBox.setWindowIcon(windowIcon);
    msgBox.setWindowTitle(titleText);
    msgBox.setText(infoText);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();

}

void MyMessageBox::setQMessageBoxWarning(QString titleText, QString infoText, QIcon windowIcon)
{

    QMessageBox msgBox;
    msgBox.setWindowIcon(windowIcon);
    msgBox.setWindowTitle(titleText);
    msgBox.setText(infoText);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();

}
