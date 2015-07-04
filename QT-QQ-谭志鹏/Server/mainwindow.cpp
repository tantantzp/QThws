#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "WinSock2.h"
#include <QtGui>
#include <QString>
#include <QMessageBox>
#include <qdebug.h>
#include <map>
#include <cstring>
#include <string>


#pragma comment(lib,"ws2_32.lib")

using namespace std;

//const SignalSender *sender=new SignalSender;

SOCKET ServerSocket;

map <QString,SOCKET> QStringMap;
map <SOCKET,QString> SOCKETMap;

DWORD WINAPI AcceptThread(LPVOID lpParamer);
DWORD WINAPI RecvThread(LPVOID lpParamer);

bool flag=false;
//QString newMessage;
bool connected=false;
bool haveIP=false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer=new QTimer(this);
    timer->setInterval(100);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_time()));
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    string IP_ADDRESS;
    QByteArray tmp =ui->lineEdit->text().toLatin1();
    IP_ADDRESS=tmp.data();
    int PORT=ui->lineEdit_2->text().toInt();

    //Create Socket
    if(WSAStartup(MAKEWORD(2,2),&Ws)!=0)
    {
        QMessageBox::warning(this,"tzp","Init Windows Socket Failed");

    }

    ServerSocket=socket(AF_INET,SOCK_STREAM,0);


    if(ServerSocket==INVALID_SOCKET)
    {
        QMessageBox::warning(this,"tzp","Create Socket Failed");

    }

    ServerAddr.sin_family=AF_INET;
    ServerAddr.sin_addr.s_addr=inet_addr(IP_ADDRESS.c_str());
    ServerAddr.sin_port=htons(PORT);
    memset(ServerAddr.sin_zero,0x00,8);
    int Ret=bind(ServerSocket,(struct sockaddr*)&ServerAddr,sizeof(ServerAddr));
    if(Ret!=0)
    {
        QMessageBox::warning(this,"tzp","Bind Socket Failed");

    }
    Ret=listen(ServerSocket,10);

    if(Ret!=0)
    {
        QMessageBox::warning(this,"tzp","Listen Socket Failed");
        this->close();
    }
    else
    {
        QMessageBox::warning(this,"tzp","listen");
    }

    DWORD ThreadId;
    HANDLE hThread=CreateThread(NULL,0,AcceptThread,(LPVOID)&ServerSocket,0,&ThreadId);
    if(hThread==NULL)
    {
        QMessageBox::warning(this,"tzp","Create UiThread Error!");

    }
    CloseHandle(hThread);
    connected=true;



}

void MainWindow::on_time()
{
    map <QString,SOCKET> ::iterator   pos;

    for(pos=QStringMap.begin();pos!=QStringMap.end();++pos)
    {
        if(pos==QStringMap.begin())
        {
            ui->textEdit->setText(pos->first);
        }
        else ui->textEdit->append(pos->first);
    }


}


DWORD WINAPI RecvThread(LPVOID lpParamer)
{

    int Ret=0;
    char *RecvBuffer=new char[MAX_PATH];
    SOCKET *ClientSocket=new SOCKET;
    ClientSocket=(SOCKET*)lpParamer;
    while(true)
    {

        memset(RecvBuffer,0,sizeof(char)*MAX_PATH);
        Ret=recv(*ClientSocket,RecvBuffer,MAX_PATH,0);

        qDebug()<<"in"<<GetCurrentThreadId()<<' '<<SOCKETMap[*ClientSocket]<<RecvBuffer;

        if(Ret==0||Ret==SOCKET_ERROR)
        {      
            qDebug()<<"Client exit!";        
        }
        else
        {        
            /*char method[100],information[260];
            memset(method,0,sizeof(char)*100);
            memset(method,0,sizeof(char)*260);
            sscanf(RecvBuffer, "%[^ ] %[^ ]", method,information);*/
            char *method=new char[100];
            sscanf(RecvBuffer, "%[^ ]", method);
            QString ReceiveIP(method);

            memset(RecvBuffer,0,sizeof(char)*MAX_PATH);
            Ret=recv(*ClientSocket,RecvBuffer,MAX_PATH,0);
            //qDebug()<<GetCurrentThreadId() <<":"<<SOCKETMap[*ClientSocket]<<"to"<<ReceiveIP<<' '<<RecvBuffer;
            send(QStringMap[ReceiveIP],RecvBuffer,MAX_PATH,0);

        }
    }
    return true;
}


DWORD WINAPI AcceptThread(LPVOID lpParamer)
{
    SOCKET *ServerSocket=(SOCKET*)lpParamer;
    SOCKET ClientSocket;
    struct sockaddr_in ClientAddr;
    DWORD ThreadId;
    while(true)
    {
        int AddrLen=sizeof(ClientAddr);//AddrLen should be initialized

        ClientSocket=accept(*ServerSocket,(struct sockaddr*)&ClientAddr,&AddrLen);

        if(ClientSocket==INVALID_SOCKET)
        {
            return false;
        }
        else
        {
            qDebug()<<"accepted!";
            QStringMap[QString(inet_ntoa(ClientAddr.sin_addr))]=ClientSocket;
            SOCKETMap[ClientSocket]=QString(inet_ntoa(ClientAddr.sin_addr));

            HANDLE hThread=CreateThread(NULL,0,RecvThread,(LPVOID)&ClientSocket,0,&ThreadId);

            if(hThread==NULL)
            {
                qDebug()<<"Create RecvThread Error!";

            }
            CloseHandle(hThread);
        }

    }
    return true;
}


void MainWindow::on_pushButton_3_clicked()
{
    ServerReceiveIP=ui->lineEdit_4->text();
    haveIP=true;
}

void MainWindow::on_pushButton_2_clicked()
{
    if(!connected)
    {
        QMessageBox::warning(this,"tzp","not connected!");
        return;
    }
    if(!haveIP)
    {
        QMessageBox::warning(this,"tzp","no IP!");
        return;
    }
    char *SendBuffer=new char[MAX_PATH];
    memset(SendBuffer,0,sizeof(char)*MAX_PATH);
    QString tmp(ui->lineEdit_3->text());
    QByteArray ba =tmp.toLatin1();
    SendBuffer=ba.data();
    send(QStringMap[ServerReceiveIP],SendBuffer,MAX_PATH,0);
    qDebug()<<"Send end!2";
}
