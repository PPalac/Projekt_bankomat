#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "operations.h"
#include "addnew.h"
#include "ui_addNew.h"
#include "sendmail.h"
#include "account.h"
#include "manage.h"
#include <QfileDialog>
#include <QValidator>
#include <QDateTime>
#include <QProcess>
#include <string>
#include <iostream>
#include <fstream>


const std::string mailTextWithdraw1 = "Witaj \nWyplaciles: ";
const std::string mailTextWithdraw2 = "zl\nAktualny stan Twojego konta wynosi: ";
const std::string mailTextWithdraw3 = "zl\n\nDziekujemy za skorzystanie z naszego bankomatu\n\n";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    ui->dispAccNumber->hide();
    ui->enterPin->setValidator(new QIntValidator);
    ui->enterPin->setVisible(false);
    ui->enterPin->setStyleSheet("background-color:white;");
    this->setStyleSheet("background-image: url(c:/images/background.png);"
                        "background-repeat: no-repeat;"
                        "background-position: center center");

    ui->card->setStyleSheet("background-image: url(c:/images/card.jpeg);"
                            "background-repeat: no-repeat;"
                            "background-position: center center");


    ui->screen->setStyleSheet("background-image: url(c:/images/page0.jpg);"
                              "background-repeat: no-repeat;"
                              "background-position: center center");
    ui->stackedWidget->setVisible(false);
    this->page = 0;

    loadCash();

    int *k = nullptr;



}
MainWindow::~MainWindow()
{
    delete ui;
}






void MainWindow::on_card_clicked()
{
    if(page == 0)
    {
        Operations operations;


        dir = QFileDialog::getOpenFileName(this,tr("Open File"),"",tr("Data files(*.dat)"));
        acc = operations.openAccount(dir);


        if(dir !="")
        {
            ui->screen->setStyleSheet("background-image: url(c:/images/page1.jpg);"
                                      "background-repeat: no-repeat;"
                                      "background-position: center center");
            ui->enterPin->setVisible(true);
            page = 1;
        }
        return;
    }

    if(page == 6 || page == 7)
    {
        QProcess process;
        process.startDetached("Projekt_bankomat",QStringList());
        qApp->quit();
    }


}



void MainWindow::on_actionDodaj_nowe_konto_triggered()
{
   addNew add;
   add.exec();
}

void MainWindow::on_actionZarzadzaj_triggered()
{
  manage manage;
  manage.exec();
}

void MainWindow::on_number0_clicked()
{
    if(page == 1 || page == 1.1 || page == 3.1)
    {
    Operations operation(ui->enterPin);
    operation.dial(0);
    }
}

void MainWindow::on_number1_clicked()
{
    if(page == 1 || page == 1.1 || page == 3.1)
    {
        Operations operation(ui->enterPin);
        operation.dial(1);

    }

}

void MainWindow::on_number2_clicked()
{
    if(page == 1 || page == 1.1 || page == 3.1)
    {
        Operations operation(ui->enterPin);
        operation.dial(2);
    }
}

void MainWindow::on_number3_clicked()
{
   if(page == 1 || page == 1.1 || page == 3.1)
    {
        Operations operation(ui->enterPin);
        operation.dial(3);
    }
}

void MainWindow::on_number4_clicked()
{
    if(page == 1 || page == 1.1 || page == 3.1)
    {
        Operations operation(ui->enterPin);
        operation.dial(4);
    }
}

void MainWindow::on_number5_clicked()
{
    if(page == 1 || page == 1.1 || page == 3.1)
    {
        Operations operation(ui->enterPin);
        operation.dial(5);
    }
}

void MainWindow::on_number6_clicked()
{
    if(page == 1 || page == 1.1 || page == 3.1)
    {
        Operations operation(ui->enterPin);
        operation.dial(6);
    }
}

void MainWindow::on_number7_clicked()
{
    if(page == 1 || page == 1.1 || page == 3.1)
    {
        Operations operation(ui->enterPin);
        operation.dial(7);
    }
}

void MainWindow::on_number8_clicked()
{
    if(page == 1 || page == 1.1 || page == 3.1)
    {
        Operations operation(ui->enterPin);
        operation.dial(8);
    }
}

void MainWindow::on_number9_clicked()
{
   if(page == 1 || page == 1.1 || page == 3.1)
    {
        Operations operation(ui->enterPin);
        operation.dial(9);
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(page == 1 || page == 1.1)
    {
        if(ui->enterPin ->text() == acc.getPin())
        {
            ui->enterPin->setVisible(false);
            ui->screen->setStyleSheet("background-image: url(c:/images/page2.jpg);"
                                  "background-repeat: no-repeat;"
                                  "background-position: center center");
            ui->dispAccNumber->setText(acc.getAccountNumber());
            ui->dispAccNumber->show();

            page = 2;
        }
        else
        {
            ui->enterPin->clear();
            ui->screen->setStyleSheet("background-image: url(c:/images/page1.1.jpg);"
                                      "background-repeat: no-repeat;"
                                      "background-position: center center");
            page = 1.1;


        }
    }

    if(page == 3.1)
    {
        Operations operation;
        int cash = ui->enterPin->text().toInt();
        if(cash<=acc.balance && operation.withdrawCash(cash,cashAmount))
        {
            acc.balance-=cash;
            operation.saveAccount(dir,acc);
            ui->screen->setStyleSheet("background-image: url(c:/images/page6.jpg);"
                                      "background-repeat: no-repeat;"
                                      "background-position: center center");
            mail(acc.mail.toStdString(),"Wyplata gotowki",mailTextWithdraw1+std::to_string(cash)+mailTextWithdraw2+std::to_string(acc.balance)+mailTextWithdraw3+acc.bankName.toStdString());
            ui->enterPin->clear();
            ui->enterPin->setVisible(false);
            ui->enterPin->setMaxLength(4);
            ui->enterPin->setEchoMode(QLineEdit::EchoMode::Password);
            page = 6;
        }
        else
        {
            ui->screen->setStyleSheet("background-image: url(c:/images/page7.jpg);"
                                      "background-repeat: no-repeat;"
                                      "background-position: center center");
            ui->enterPin->hide();
            page = 7;
        }
    }
    if(page == 4)
    {
        Operations operation;
        int cash = ui->enterPin->text().toInt();
        acc.balance+=cash;
        operation.saveAccount(dir,acc);
        ui->screen->setStyleSheet("background-image: url(c:/images/page6.jpg);"
                                  "background-repeat: no-repeat;"
                                  "background-position: center center");
        ui->enterPin->hide();
        ui->stackedWidget->hide();
        page = 6;



    }
}

void MainWindow::on_selectButton1_clicked()
{
    Operations operation;
    if (page == 3 )
    {
        if(acc.balance>=10 && operation.withdrawCash(10,cashAmount))
        {
            acc.balance-=10;

            operation.saveAccount(dir,acc);
            ui->screen->setStyleSheet("background-image: url(c:/images/page6.jpg);"
                                      "background-repeat: no-repeat;"
                                      "background-position: center center");
            mail(acc.mail.toStdString(),"Wyplata gotowki",mailTextWithdraw1+"10"+mailTextWithdraw2+std::to_string(acc.balance)+mailTextWithdraw3+acc.bankName.toStdString());

            page = 6;

        }
        else
        {
            ui->screen->setStyleSheet("background-image: url(c:/images/page7.jpg);"
                                      "background-repeat: no-repeat;"
                                      "background-position: center center");
            page = 7;
        }


    }



}

void MainWindow::on_selectButton2_clicked()
{
    Operations operation;
    if (page == 2)
    {
        ui->screen->setStyleSheet("background-image: url(c:/images/page3.jpg);"
                                  "background-repeat: no-repeat;"
                                  "background-position: center center");
        page = 3;
        return;
    }
    if (page == 3)
    {
        if(acc.balance>=20 && operation.withdrawCash(20,cashAmount) )
        {
            acc.balance-=20;

            operation.saveAccount(dir,acc);
            ui->screen->setStyleSheet("background-image: url(c:/images/page6.jpg);"
                                      "background-repeat: no-repeat;"
                                      "background-position: center center");
            mail(acc.mail.toStdString(),"Wyplata gotowki",mailTextWithdraw1+"20"+mailTextWithdraw2+std::to_string(acc.balance)+mailTextWithdraw3+acc.bankName.toStdString());
            page = 6;


        }
        else
        {
            ui->screen->setStyleSheet("background-image: url(c:/images/page7.jpg);"
                                      "background-repeat: no-repeat;"
                                      "background-position: center center");
            page = 7;
        }

        return;
    }
}

void MainWindow::on_selectButton3_clicked()
{
    Operations operation;
    if(page == 2)
    {
        ui->screen->setStyleSheet("background-image: url(c:/images/page5.jpg);"
                          "background-repeat: no-repeat;"
                          "background-position: center center");
        ui->enterPin->setVisible(true);
        ui->enterPin->setEchoMode(QLineEdit::EchoMode::Normal);
        ui->enterPin->setMaxLength(12);
        ui->enterPin->setText(QString::number(acc.balance));
        page = 5;
        return;
    }
    if(page == 5)
    {
        ui->screen->setStyleSheet("background-image: url(c:/images/page2.jpg);"
                          "background-repeat: no-repeat;"
                          "background-position: center center");
        ui->enterPin->clear();
        ui->enterPin->setEchoMode(QLineEdit::EchoMode::Password);
        ui->enterPin->setMaxLength(4);
        ui->enterPin->setVisible(false);
        page = 2;
        return;
    }

    if (page == 3 )
    {
        if(acc.balance>=50 && operation.withdrawCash(50,cashAmount))
        {
            acc.balance-=50;

            operation.saveAccount(dir,acc);
            ui->screen->setStyleSheet("background-image: url(c:/images/page6.jpg);"
                                      "background-repeat: no-repeat;"
                                      "background-position: center center");
            mail(acc.mail.toStdString(),"Wyplata gotowki",mailTextWithdraw1+"50"+mailTextWithdraw2+std::to_string(acc.balance)+mailTextWithdraw3+acc.bankName.toStdString());
            page = 6;
        }
        else
        {
            ui->screen->setStyleSheet("background-image: url(c:/images/page7.jpg);"
                                      "background-repeat: no-repeat;"
                                      "background-position: center center");
            page = 7;
        }


    }

}

void MainWindow::on_selectButton4_clicked()
{
    Operations operation;
    if (page == 3)
    {
        if(acc.balance>=100 && operation.withdrawCash(100,cashAmount))
        {
            acc.balance-=10;

            operation.saveAccount(dir,acc);
            ui->screen->setStyleSheet("background-image: url(c:/images/page6.jpg);"
                                      "background-repeat: no-repeat;"
                                      "background-position: center center");
            mail(acc.mail.toStdString(),"Wyplata gotowki",mailTextWithdraw1+"100"+mailTextWithdraw2+std::to_string(acc.balance)+mailTextWithdraw3+acc.bankName.toStdString());
            page = 6;
        }
        else
        {
            ui->screen->setStyleSheet("background-image: url(c:/images/page7.jpg);"
                                      "background-repeat: no-repeat;"
                                      "background-position: center center");
            page = 7;
        }


    }
}

void MainWindow::on_selectButton5_clicked()
{
    Operations operation;
    if (page == 3)
    {
        if(acc.balance>=200 && operation.withdrawCash(200,cashAmount))
        {
            acc.balance-=200;

            operation.saveAccount(dir,acc);
            ui->screen->setStyleSheet("background-image: url(c:/images/page6.jpg);"
                                      "background-repeat: no-repeat;"
                                      "background-position: center center");
            mail(acc.mail.toStdString(),"Wyplata gotowki",mailTextWithdraw1+"200"+mailTextWithdraw2+std::to_string(acc.balance)+mailTextWithdraw3+acc.bankName.toStdString());
            page = 6;
        }

        else
        {
            ui->screen->setStyleSheet("background-image: url(c:/images/page7.jpg);"
                                      "background-repeat: no-repeat;"
                                      "background-position: center center");
            page = 7;
        }

    }
    if(page == 2)
    {ui->screen->setStyleSheet("background-image: url(c:/images/page4.jpg);"
                                  "background-repeat: no-repeat;"
                                  "background-position: center center");
    ui->enterPin->setVisible(true);
    ui->enterPin->setEchoMode(QLineEdit::EchoMode::Normal);
    ui->enterPin->setMaxLength(10);
    ui->enterPin->clear();


        ui->stackedWidget->setVisible(true);
        page = 4;
        return;
    }
}

void MainWindow::on_selectButton6_clicked()
{
    if (page == 3)
    {
        ui->screen->setStyleSheet("background-image: url(c:/images/page3.1.jpg);"
                                  "background-repeat: no-repeat;"
                                  "background-position: center center");
        ui->enterPin->clear();
        ui->enterPin->setVisible(true);
        ui->enterPin->setMaxLength(10);
        ui->enterPin->setEchoMode(QLineEdit::EchoMode::Normal);

        page = 3.1;

    }
}

void MainWindow::on_cancel_clicked()
{
    ui->screen->setStyleSheet("background-image: url(c:/images/page6.jpg);"
                      "background-repeat: no-repeat;"
                      "background-position: center center");
    ui->enterPin->setVisible(false);
    ui->stackedWidget->hide();
    page = 6;
}

void MainWindow::on_modify_clicked()
{
    if (page == 1 || page == 1.1 || page == 3.1 )
    {
        ui->enterPin->clear();
    }

}


void MainWindow ::loadCash()
{
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
}

int MainWindow::sumSliders()
{
   int sum = ui->lcdNumber->value()+ui->lcdNumber_2->value()*2+ui->lcdNumber_3->value()*5+ui->lcdNumber_4->value()*10;
   sum+=ui->lcdNumber_7->value()*20+ui->lcdNumber_8->value()*50+ui->lcdNumber_6->value()*100+ui->lcdNumber_5->value()*200;

   return sum;

}




void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    QString sum = QString::number(sumSliders());
    ui->enterPin->setText(sum);
}

void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    QString sum = QString::number(sumSliders());
    ui->enterPin->setText(sum);
}

void MainWindow::on_horizontalSlider_3_sliderMoved(int position)
{
    QString sum = QString::number(sumSliders());
    ui->enterPin->setText(sum);
}

void MainWindow::on_horizontalSlider_4_sliderMoved(int position)
{
    QString sum = QString::number(sumSliders());
    ui->enterPin->setText(sum);
}

void MainWindow::on_horizontalSlider_5_sliderMoved(int position)
{
    QString sum = QString::number(sumSliders());
    ui->enterPin->setText(sum);
}

void MainWindow::on_horizontalSlider_6_sliderMoved(int position)
{
    QString sum = QString::number(sumSliders());
    ui->enterPin->setText(sum);
}

void MainWindow::on_horizontalSlider_7_sliderMoved(int position)
{
    QString sum = QString::number(sumSliders());
    ui->enterPin->setText(sum);
}

void MainWindow::on_horizontalSlider_8_sliderMoved(int position)
{
    QString sum = QString::number(sumSliders());
    ui->enterPin->setText(sum);
}
