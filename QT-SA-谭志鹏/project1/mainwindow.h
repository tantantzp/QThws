#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "Layout.h"
#include "PackingCommand.h"
#include "PackingStrategy.h"
#include "Point.h"
#include "Rect.h"
#include "SPPackingCommand.h"
#include "SPPackingStrategy.h"
#include "GraphPacking.h"
#include "dialog.h"
#include "dialog_2.h"
#include <QPoint>

namespace Ui {
class MainWindow;
}

using namespace RECTPACKING;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *ev);
    float next();
    void find();
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
private slots:
    void on_action_triggered();
    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_action_4_triggered();

    void on_action_5_triggered();

    void on_add();

private:
    Ui::MainWindow *ui;
    int num;
    Layout layout;
    SPPackingStrategy * strategy;
    Dialog setDialog;
    Dialog_2 setDialog_2;
    int rectClicked;
    int T;
    int I;
    float rate;
    QPoint initPoint;

};

#endif // MAINWINDOW_H
