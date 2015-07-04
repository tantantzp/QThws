#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "WinSock2.h"
#include <Windows.h>
#include <QtGui>
#include <QString>
#include <QMessageBox>

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
public slots:
    void on_time();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    char* RecvBuffer;
    WSADATA Ws;
    SOCKET ClientSocket;

    struct sockaddr_in ServertAddr;
    int Ret;
    int AddrLen;
    QString ReceiveIP;
};

#endif // MAINWINDOW_H
