#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "WinSock2.h"
#include <Windows.h>
#include <QtGui>
#include <QString>
#include <QMessageBox>
#include <QTimer>
#pragma comment(lib,"ws2_32.lib")


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}
void MainWindow::on_pushButton_2_clicked()
{
    Ret=0;
    AddrLen=0;
    char *IP_ADDRESS=new char[MAX_PATH];
    memset(IP_ADDRESS,0,sizeof(char)*MAX_PATH);
    QByteArray tmp =ui->lineEdit_3->text().toLatin1();
    IP_ADDRESS=tmp.data();

    int PORT=ui->lineEdit_4->text().toInt();

    //Create Socket
    if(WSAStartup(MAKEWORD(2,2),&Ws)!=0)
    {
        QMessageBox::warning(this,"tzp","Init Windows Socket Failed");

    }
    u_long iMode=1;
    ClientSocket=socket(AF_INET,SOCK_STREAM,0);
    ioctlsocket(ClientSocket, FIONBIO, &iMode);

    if(ClientSocket==INVALID_SOCKET)
    {
        QMessageBox::warning(this,"tzp","Create Socket Failed");

    }

    ServertAddr.sin_family=AF_INET;
    ServertAddr.sin_addr.s_addr=inet_addr(IP_ADDRESS);
    ServertAddr.sin_port=htons(PORT);
    memset(ServertAddr.sin_zero,0x00,8);

    Ret=::connect(ClientSocket,(struct sockaddr*)&ServertAddr,sizeof(ServertAddr));
    if(Ret==SOCKET_ERROR)
    {
        //QMessageBox::warning(this,"tzp","connect Error::");

    }
    else
    {
       QMessageBox::warning(this,"tzp","connect success");
    }

    RecvBuffer=new char[MAX_PATH];
    memset(RecvBuffer,0,sizeof(char)*MAX_PATH);
    ui->lineEdit->setText("please input information");
    QTimer *timer=new QTimer(this);
    timer->setInterval(100);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_time()));
    timer->start();
}
MainWindow::~MainWindow()
{
    delete ui;
    delete RecvBuffer;

}

void MainWindow::on_time()
{
    update();
    run();
}


void MainWindow::run()
{

    // ui->lineEdit_2->setText(QString(inet_ntoa(ClientAddr.sin_addr)));

     Ret=0;

     memset(RecvBuffer,0,sizeof(char)*MAX_PATH);

     Ret=recv(ClientSocket,RecvBuffer,MAX_PATH,0);


     if(Ret==0||Ret==SOCKET_ERROR)
     {
         //QMessageBox::warning(0,"tzp","Client exit!");
         return;
     }
     else
     {
         QString tmp("Received information:");
         tmp.append(RecvBuffer);
         ui->textEdit->append(tmp);
     }


}

void MainWindow::on_pushButton_clicked()
{
    char *SendBuffer=new char[MAX_PATH];
    memset(SendBuffer,0,sizeof(char)*MAX_PATH);

    QString tmp(ReceiveIP);
    QByteArray ba =tmp.toLatin1();
    SendBuffer=ba.data();
    Ret=send(ClientSocket,SendBuffer,(int)strlen(SendBuffer),0);

    if(Ret==SOCKET_ERROR)
    {
        QMessageBox::warning(this,"tzp","send info error!");

    }

    QString tmp2(ui->lineEdit->text());
    QByteArray ba2 =tmp2.toLatin1();
    SendBuffer=ba2.data();


    qDebug()<<SendBuffer;
    Ret=send(ClientSocket,SendBuffer,(int)strlen(SendBuffer),0);

    if(Ret==SOCKET_ERROR)
    {
        QMessageBox::warning(this,"tzp","send info error!");

    }
    QString tmp3("Send information:");
    tmp3.append(SendBuffer);
    ui->textEdit->append(tmp3);
}



void MainWindow::on_pushButton_3_clicked()
{
    this->ReceiveIP=ui->lineEdit_2->text();
}
