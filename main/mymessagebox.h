#ifndef MYMESSAGEBOX_H
#define MYMESSAGEBOX_H

#include "headers.h"

class MyMessageBox
{

public:
    MyMessageBox();
    ~MyMessageBox();

    void setQMessageBoxInformation(QString, QString, QIcon);
    void setQMessageBoxQuestion();
    void setQMessageBoxWarning(QString, QString, QIcon);
    void setQMessageBoxCritical();

};

#endif
