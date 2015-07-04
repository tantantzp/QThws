#include "dialog_2.h"
#include "ui_dialog_2.h"

Dialog_2::Dialog_2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_2)
{
    ui->setupUi(this);
}

Dialog_2::~Dialog_2()
{
    delete ui;
}

void Dialog_2::on_lineEdit_textChanged(const QString &arg1)
{
    width=arg1.toInt();
}

void Dialog_2::on_lineEdit_2_textChanged(const QString &arg1)
{
    height=arg1.toInt();
}

void Dialog_2::on_buttonBox_accepted()
{
    emit add();
}
