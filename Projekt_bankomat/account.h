#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <qstring.h>
class account
{
public:
    account();
    QString name;
    QString surname;
    QString mail;
    int balance;
    QString bankName;
    void setPin(QString myPin){pin = myPin;}
    void setPesel(int myPesel){pesel = myPesel;}
    QString getPin() const {return pin;}
    int getPesel() const {return pesel;}
    void setAccountNumber(QString number){accountNumber = number;}
    QString getAccountNumber() const {return accountNumber;}
private:
    int pesel;
    QString pin;
    QString accountNumber;


};

#endif // ACCOUNT_H
