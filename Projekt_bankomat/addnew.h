#ifndef ADDNEW_H
#define ADDNEW_H

#include <QDialog>
#include <QAbstractButton>
#include <QDataStream>

namespace Ui {
class addNew;
}

class addNew : public QDialog
{
    Q_OBJECT

public:
    explicit addNew(QWidget *parent = 0);
    ~addNew();


private slots:


    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::addNew *ui;
    void saveAccount();
    QString generateAccountNumber(int index);
    const int bankNumbers[5] = {1020,1050,1090,1140,1240};
    const QString bankNames[5] = {"PKO BP", "ING", "BZ WBK", "mBank", "Pekao"};
    int ID;
    void saveID();
    void getID();


};

#endif // ADDNEW_H
