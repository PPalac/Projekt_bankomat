#include "manage.h"
#include "ui_manage.h"
#include <QFile>
#include <iostream>
#include <fstream>


manage::manage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manage)
{
    ui->setupUi(this);
    ui->amountEdit1->setValidator(new QIntValidator);
    ui->amountEdit2->setValidator(new QIntValidator);
    ui->amountEdit5->setValidator(new QIntValidator);
    ui->amountEdit10->setValidator(new QIntValidator);
    ui->amountEdit20->setValidator(new QIntValidator);
    ui->amountEdit50->setValidator(new QIntValidator);
    ui->amountEdit100->setValidator(new QIntValidator);
    ui->amountEdit200->setValidator(new QIntValidator);

    std::ifstream file("manage.txt");
    if(file.is_open() )
    {

        for(int i = 0; i<8; i++)
        {
            file>>cashAmount[i];

        }
        file.close();
        }
        else
        {
            std::ofstream tempFile("manage.txt");
            for(int i = 0; i<8; i++)
            {
                cashAmount[i] = 0;
                tempFile<<cashAmount[i]<<" ";
            }
            tempFile.close();
        }

    setPercentage();








}

manage::~manage()
{
    delete ui;
}



void manage::saveAmount()
{
    std::ofstream file("manage.txt");
    if(file.is_open())
    {
        cashAmount[0] += ui->amountEdit1->text().toInt();
        cashAmount[1] += ui->amountEdit2->text().toInt();
        cashAmount[2] += ui->amountEdit5->text().toInt();
        cashAmount[3] += ui->amountEdit10->text().toInt();
        cashAmount[4] += ui->amountEdit20->text().toInt();
        cashAmount[5] += ui->amountEdit50->text().toInt();
        cashAmount[6] += ui->amountEdit100->text().toInt();
        cashAmount[7] += ui->amountEdit200->text().toInt();

        for(int i = 0; i<8; i++)
        {
            if(cashAmount[i]<maxAmount[i])
                file<<cashAmount[i]<<" ";
            else
            {
                file<<maxAmount[i]<<" ";
                cashAmount[i] = maxAmount[i];
            }
        }
        file.close();

    }
}

void manage::setPercentage()
{

    ui->amount1->setValue(cashAmount[0]*100/maxAmount[0]);
    ui->amount2->setValue(cashAmount[1]*100/maxAmount[1]);
    ui->amount5->setValue(cashAmount[2]*100/maxAmount[2]);
    ui->amount10->setValue(cashAmount[3]*100/maxAmount[3]);
    ui->amount20->setValue(cashAmount[4]*100/maxAmount[4]);
    ui->amount50->setValue(cashAmount[5]*100/maxAmount[5]);
    ui->amount100->setValue(cashAmount[6]*100/maxAmount[6]);
    ui->amount200->setValue(cashAmount[7]*100/maxAmount[7]);
}





void manage::on_pushButton_2_clicked()
{
    saveAmount();
    setPercentage();
}

void manage::on_pushButton_clicked()
{
    this->close();
}
