#ifndef MANAGE_H
#define MANAGE_H

#include <QDialog>


namespace Ui {
class manage;
}

class manage : public QDialog
{
    Q_OBJECT

public:
    explicit manage(QWidget *parent = 0);
    ~manage();

private slots:


    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::manage *ui;
    int cashAmount[8];
    int maxAmount[8] = {200,200,200,400,400,300,300,200};
    void saveAmount();
    void setPercentage();
};

#endif // MANAGE_H
