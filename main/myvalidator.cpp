#include "myvalidator.h"

MyValidator::MyValidator()
{
    this->validator = nullptr;
}

MyValidator::~MyValidator()
{
    if(this->validator != nullptr)
        delete validator;
}

void MyValidator::setLoginLineEditValidator(QLineEdit *&lineEdit)
{
    QRegularExpression regexLogin("^[a-zA-Z0-9]{6,20}$");
    QValidator *validator = new QRegularExpressionValidator(regexLogin);

    lineEdit->setValidator(validator);
}

void MyValidator::setPasswordLineEditValidator(QLineEdit *&lineEdit)
{
    QRegularExpression regexPassword("^[a-zA-Z0-9]{8,20}$");
    QValidator *validator = new QRegularExpressionValidator(regexPassword);

    lineEdit->setValidator(validator);
}

void MyValidator::setLatinLineEditValidator(QLineEdit *&lineEdit, int size)
{
    QRegularExpression regexLatin("^[a-zA-Z0-9]{" + QString::number(size) + "}$");
    regexLatin.setPatternOptions(QRegularExpression::UseUnicodePropertiesOption);

    QValidator *validator = new QRegularExpressionValidator(regexLatin);
    validator->setLocale(QLocale::Latin);

    lineEdit->setValidator(validator);
}

void MyValidator::setIntegerLineEditValidator(QLineEdit *&lineEdit, int size)
{
    QRegularExpression regexInteger("^[0-9]{" + QString::number(size) + "}$");
    QValidator *validator = new QRegularExpressionValidator(regexInteger);

    lineEdit->setValidator(validator);
}

void MyValidator::setCyrillicLineEditValidator(QLineEdit *&lineEdit, int size)
{
    QRegularExpression regexCyrillic ("^[а-яА-яа-яА-яІіЇїЄє]{" + QString::number(size) + "}$");
    regexCyrillic.setPatternOptions(QRegularExpression::UseUnicodePropertiesOption);

    QValidator *validator  = new QRegularExpressionValidator(regexCyrillic);
    validator->setLocale(QLocale::AnyLanguage);

    lineEdit->setValidator(validator);
}

void MyValidator::setAdressLineEditValidator(QLineEdit *&lineEdit)
{
    QRegularExpression regexCyrillic ("^[ ,/.0-9а-яА-яа-яА-яІіЇїЄє]*$");
    regexCyrillic.setPatternOptions(QRegularExpression::UseUnicodePropertiesOption);

    QValidator *validator  = new QRegularExpressionValidator(regexCyrillic);
    validator->setLocale(QLocale::AnyLanguage);

    lineEdit->setValidator(validator);
}

void MyValidator::setGeneralSearchLineEditValidator(QLineEdit *&lineEdit)
{
    QRegularExpression regexCyrillic ("^[0-9a-zA-Zа-яА-яа-яА-яІіЇїЄє]*$");
    regexCyrillic.setPatternOptions(QRegularExpression::UseUnicodePropertiesOption);

    QValidator *validator  = new QRegularExpressionValidator(regexCyrillic);
    validator->setLocale(QLocale::AnyLanguage);

    lineEdit->setValidator(validator);
}
