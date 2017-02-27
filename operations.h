#ifndef OPERATIONS_H
#define OPERATIONS_H
#include <QGraphicsView>
#include <QMainWindow>
#include <QLineEdit>
#include <QDataStream>
#include "account.h"
#include "mainwindow.h"
#include "addnew.h"


class Operations
{
public:

    Operations();
    Operations(QLineEdit *edit);
    QLineEdit *edit;

    void dial(int digit);
    account openAccount(QString dir);
    void saveAccount(QString dir, account acc);
    void saveNewAccount(account acc, QString dir);
    bool withdrawCash(int amount, int cashAmount[8]);


private:


    int value[8] = {1,2,5,10,20,50,100,200};
    int maxAmount[8] = {200,200,200,400,400,300,300,200};
    void saveCash(int cash[8]);

};


#endif // OPERATIONS_H
