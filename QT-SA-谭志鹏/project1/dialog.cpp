#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    T=50;
    I=10;
    rate=0.5;
    ui->lineEdit->setText(QString::number(50));
    ui->lineEdit_2->setText(QString::number(10));
    ui->lineEdit_3->setText(QString::number(0.5));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_lineEdit_textChanged(const QString &arg1)
{
    T=arg1.toInt();
}

void Dialog::on_lineEdit_2_textChanged(const QString &arg1)
{
    I=arg1.toInt();
}

void Dialog::on_lineEdit_3_textChanged(const QString &arg1)
{
    rate=arg1.toFloat();
}
