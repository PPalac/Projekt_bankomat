#include "addnew.h"
#include "ui_addnew.h"
#include "account.h"
#include "operations.h"
#include <QMessageBox>
#include <QDoubleValidator>
#include <QIntValidator>
#include <fstream>
#include <QFileDialog>
#include <QDataStream>



addNew::addNew(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNew)
{
    ui->setupUi(this);
    ui->accountBalance->setValidator(new QIntValidator);
    ui->pin->setValidator(new QIntValidator);
    ui->pinAgain->setValidator(new QIntValidator);
    ui->pesel->setValidator(new QDoubleValidator);
    ui->pesel->setMaxLength(11);


}

addNew::~addNew()
{
    delete ui;
}





void addNew::on_pushButton_2_clicked()
{
    this->close();
}

void addNew::on_pushButton_clicked()
{

    if (ui->pin->text() != ui->pinAgain->text())
    {
        QMessageBox::information(this,"Error!","PIN różny!");
        return;
    }
    int index = ui->comboBox->currentIndex();
    account add;



    QString dir = QFileDialog::getSaveFileName(this,tr("Save File"),"",tr("Data files (*.dat)"));

        add.setPin( ui->pin->text());
        add.name = ui->name->text();
        add.surname = ui->surname->text();
        add.balance = ui->accountBalance->text().toDouble();
        add.setPesel(ui->pesel->text().toInt());
        add.mail = ui->mail->text();
        add.setAccountNumber(generateAccountNumber(index));
        add.bankName = bankNames[index];

        Operations operation;
        operation.saveNewAccount(add,dir);


        this->close();





}
QString addNew::generateAccountNumber(int index)
{
    QString number = QString::number(bankNumbers[index]);
    getID();
    ID++;
    saveID();
    QString IDtemp = QString::number(ID);
    QString completeNumber = number+IDtemp;
    return completeNumber;



}
void addNew::saveID()
{

    std::ofstream file("ID.txt");
    if(file.is_open())
    {
        file<<ID;
    }
    file.close();


}
void addNew::getID()
{
    std::ifstream file("ID.txt");
    if(file.is_open() )
    {
        file>>ID;
        file.close();
    }
    else
    {
        ID = 1000000;
    }


}


