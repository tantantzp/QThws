#ifndef DIALOG_2_H
#define DIALOG_2_H

#include <QDialog>

namespace Ui {
class Dialog_2;
}

class Dialog_2 : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog_2(QWidget *parent = 0);
    ~Dialog_2();
    int width;
    int height;
signals:
    void add();
private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_buttonBox_accepted();

private:
    Ui::Dialog_2 *ui;
};

#endif // DIALOG_2_H
