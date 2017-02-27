#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "account.h"



namespace Ui {
class MainWindow;
class addNew;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static int a;



private slots:
    void on_selectButton1_clicked();


    void on_card_clicked();

    void on_actionDodaj_nowe_konto_triggered();
    void on_actionZarzadzaj_triggered();

    void on_number0_clicked();

    void on_number2_clicked();

    void on_number3_clicked();

    void on_number1_clicked();

    void on_number4_clicked();

    void on_number5_clicked();

    void on_number6_clicked();

    void on_number7_clicked();

    void on_number8_clicked();

    void on_number9_clicked();

    void on_pushButton_clicked();

    void on_selectButton2_clicked();

    void on_selectButton3_clicked();

    void on_selectButton4_clicked();

    void on_selectButton5_clicked();

    void on_selectButton6_clicked();

    void on_cancel_clicked();

    void on_modify_clicked();

    int sumSliders();



    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_2_sliderMoved(int position);

    void on_horizontalSlider_3_sliderMoved(int position);

    void on_horizontalSlider_4_sliderMoved(int position);

    void on_horizontalSlider_5_sliderMoved(int position);

    void on_horizontalSlider_6_sliderMoved(int position);

    void on_horizontalSlider_7_sliderMoved(int position);

    void on_horizontalSlider_8_sliderMoved(int position);

private:
     Ui::MainWindow *ui;
     double page;
     account acc;
     QString dir;
     int cashAmount[8];


     void loadCash();

};

#endif // MAINWINDOW_H
