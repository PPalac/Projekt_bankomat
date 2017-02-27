#include "operations.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "account.h"
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <fstream>



Operations::Operations()
{

}
Operations::Operations(QLineEdit *edit)
{
    Operations::edit = edit;
}

QDataStream &operator<<( QDataStream &stream, const account &data )
{
  stream << data.name << data.surname << data.getPin() << data.balance << data.getPesel() << data.mail<<data.getAccountNumber()<<data.bankName;

  return stream;
}

QDataStream &operator>>( QDataStream &stream, account &data )
{
  QString myPin;
  int myPesel;
  QString myNumber;
  stream >> data.name;
  stream >> data.surname;
  stream >> myPin;
  stream >> data.balance;
  stream >> myPesel;
  stream >> data.mail;
  stream >> myNumber;
  stream>> data.bankName;
  data.setPin(myPin);
  data.setPesel(myPesel);
  data.setAccountNumber(myNumber);

  return stream;
}



account Operations::openAccount(QString dir)
{
    account read;


    QFile file(dir);

     if(file.open(QIODevice::ReadOnly))
     {
         QDataStream stream(&file);
         stream.setVersion(QDataStream::Qt_5_7);
         stream >> read;
         file.close();

     }


     return read;

}

void Operations::dial(int digit)
{
    QString text = edit->text();
    switch (digit)
    {
    case 0:
        edit->setText(text+"0");
        break;
    case 1:
        edit->setText(text+"1");
        break;
    case 2:
        edit->setText(text+"2");
        break;
    case 3:
        edit->setText(text+"3");
        break;
    case 4:
        edit->setText(text+"4");
        break;
    case 5:
        edit->setText(text+"5");
        break;
    case 6:
        edit->setText(text+"6");
        break;
    case 7:
        edit->setText(text+"7");
        break;
    case 8:
        edit->setText(text+"8");
        break;
    case 9:
        edit->setText(text+"9");
        break;
    }

}

void Operations::saveAccount(QString dir, account acc)
{
    QFile file(dir);
    if(file.open(QIODevice::WriteOnly))

    {

        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_5_7);
        stream << acc;
        file.close();

    }
    else
        return;
}

void Operations::saveNewAccount(account acc, QString dir)
{
    QFile file(dir);
    if(file.open(QIODevice::WriteOnly))

    {

        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_5_7);
        stream << acc;
        file.close();

    }
    else
       {

        return;
       }
}



bool Operations::withdrawCash(int amount, int cashAmount[8])
{


        for(int i = 7; i>=0;i--)
        {
            while(amount >= value[i] && cashAmount[i]>0)
            {
                cashAmount[i]--;
                amount-=value[i];
            }
        }
        if(amount == 0)
        {
            saveCash(cashAmount);
            return true;
        }
        else
            return false;



}

void Operations::saveCash(int cash[])
{
    std::ofstream file("manage.txt");
    if(file.is_open())
    {


        for(int i = 0; i<8; i++)
        {
            if(cash[i]<maxAmount[i])
                file<<cash[i]<<" ";
            else
            {
                file<<maxAmount[i]<<" ";
                cash[i] = maxAmount[i];
            }
        }
        file.close();

    }
}


