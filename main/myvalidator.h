#ifndef MYVALIDATOR_H
#define MYVALIDATOR_H

#include "headers.h"

class MyValidator
{

protected:
    QValidator *validator;

public:
    MyValidator();
    ~MyValidator();

    void setLoginLineEditValidator(QLineEdit *&);
    void setPasswordLineEditValidator(QLineEdit *&);

    void setLatinLineEditValidator(QLineEdit *&, int);
    void setIntegerLineEditValidator(QLineEdit *&, int);
    void setCyrillicLineEditValidator(QLineEdit *&, int);

    void setAdressLineEditValidator(QLineEdit *&);

    void setGeneralSearchLineEditValidator(QLineEdit *&);
};

#endif
