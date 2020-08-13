#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->pbCoffee->setEnabled(false);
    ui->pbTea->setEnabled(false);
    ui->pbMilk->setEnabled(false);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pb10_clicked()
{
    changeMoney(10,*ui);
}

void Widget::on_pb50_clicked()
{
    changeMoney(50, *ui);
}

void Widget::on_pb100_clicked()
{
    changeMoney(100, *ui);
}

void Widget::on_pb500_clicked()
{
    changeMoney(500, *ui);
}

void Widget::on_pbCoffee_clicked()
{
    changeMoney(-COFFEE_VAL, *ui);
}

void Widget::on_pbTea_clicked()
{
    changeMoney(-TEA_VAL, *ui);
}

void Widget::on_pbMilk_clicked()
{
    changeMoney(-MILK_VAL, *ui);
}

void Widget::on_pbReset_clicked()
{
    QMessageBox m;
    // Count change
    int cntFiveHundread = 0;
    int cntOneHundread = 0;
    int cntFifth = 0;
    int cntTen = 0;

    // Calculate change by Easy Change Algorithm(Not use greedy)
    while(money >= 500)
    {
        money -= 500;
        cntFiveHundread++;
    }

    while(money >= 100)
    {
        money -= 100;
        cntOneHundread++;
    }

    while(money >= 50)
    {
        money -= 50;
        cntFifth++;
    }

    while(money >= 10)
    {
        money -= 10;
        cntTen++;
    }

    // Renew ui
    changeMoney(0, *ui);

    // Print change list
    char temp[40];
    sprintf(temp, "500 : %d\n100 : %d\n50 : %d\n10 : %d", cntFiveHundread, cntOneHundread, cntFifth, cntTen);
    m.information(nullptr,"Your Change",temp);
}

void Widget::on_pbHello_clicked()
{
    QMessageBox m;
    m.information(nullptr,"Hello","Created By BoB 9th Kim Cheong-Jun");
}
