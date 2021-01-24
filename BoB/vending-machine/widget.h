#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include "ui_widget.h"

// Set Merchandise's value
#define COFFEE_VAL 100
#define TEA_VAL 150
#define MILK_VAL 200

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    int money {0};

    // Change money status and renew UI
    void changeMoney(int diff, Ui::Widget ui)
    {
        money += diff;
        ui.lcdNumber->display(money);

        // Enable and Unable Button depend on money
        if(money >= COFFEE_VAL)
            ui.pbCoffee->setEnabled(true);
        else
            ui.pbCoffee->setEnabled(false);

        if(money >= TEA_VAL)
            ui.pbTea->setEnabled(true);
        else
            ui.pbTea->setEnabled(false);

        if(money >= MILK_VAL)
            ui.pbMilk->setEnabled(true);
        else
            ui.pbMilk->setEnabled(false);
    };


private slots:
    void on_pb10_clicked();

    void on_pb50_clicked();

    void on_pb100_clicked();

    void on_pb500_clicked();

    void on_pbCoffee_clicked();

    void on_pbTea_clicked();

    void on_pbMilk_clicked();

    void on_pbReset_clicked();

    void on_pbHello_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
