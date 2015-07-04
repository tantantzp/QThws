#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "WinSock2.h"
#include <QtGui>
#include <map>
#include "WinSock2.h"
#include <Windows.h>
#include <QString>
#include <QMessageBox>
#include <QTimer>
#include <string>

#pragma comment(lib,"ws2_32.lib")

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void run();
private slots:
    void on_pushButton_clicked();
    void on_time();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();

signals:
    void ClientAdd(QString q);

private:
    Ui::MainWindow *ui;
    WSADATA Ws;
    struct sockaddr_in ServerAddr;
    QString ServerReceiveIP;

};

#endif // MAINWINDOW_H
