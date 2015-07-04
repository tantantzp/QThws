#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QFIleDialog>
#include <QString>
#include "Rect.h"
#include <QDebug>
#include <QMessageBox>
#include <vector>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QColor>
#include "Point.h"
#include <QPoint>
#include <Windows.h>
#include <ctime>
#include <cmath>
#include <dialog.h>
#include <QMouseEvent>
#include <dialog_2.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&this->setDialog_2,SIGNAL(add()),this,SLOT(on_add()));
    num=0;
    //this->layout=new Layout();
    strategy=new SPPackingStrategy();
    T=50;
    I=10;
    rate=0.5;
    rectClicked=-1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    QPen pen(Qt::black);
    QBrush brush(Qt::green);
    QBrush brush2(Qt::red);
    p.setPen(pen);
    p.setBrush(brush);
    Point tmpPoint;
    Rect tmpRect;

    for(int i=0;i<this->num;i++)
    {
      if(this->rectClicked==i)
      {
         p.setBrush(brush2);
         tmpRect=this->layout.getRect(i);
         tmpPoint=tmpRect.lb;
         p.drawRect(tmpPoint.x+20,tmpPoint.y+60,tmpRect.width,tmpRect.height);
      }
      else
      {
          p.setBrush(brush);
          tmpRect=this->layout.getRect(i);
          tmpPoint=tmpRect.lb;
          p.drawRect(tmpPoint.x+20,tmpPoint.y+60,tmpRect.width,tmpRect.height);
      }
    }

}

void MainWindow::on_action_triggered()
{
    QString fn=QFileDialog::getOpenFileName(this,tr("打开设置文件"),".",tr("文本文件(*.txt)"));
    if(!fn.isEmpty())
    {
        if(QFile::exists(fn))
        {
            QFile file(fn);
            if(file.open(QFile::ReadOnly))
            {
                num=0;
                strategy=new SPPackingStrategy();
                Layout newLayout;
                layout=newLayout;
                QTextStream fin(&file);
                fin>>num;
                Rect tmpRect;
                rectClicked=-1;

                //QString s=QString::number(num);
                for(int i=0;i<num;i++)
                {
                    int w,h;
                    fin>>w>>h;
                    tmpRect.setRect(w*10,h*10);
                    this->layout.addRect(tmpRect);
                    //QMessageBox::information(this,tr("tzp"),s);
               }
               strategy->initialPacking(this->layout);
               update();
               QMessageBox::information(this,tr("tzp"),"begin");
               float initarea=layout.compArea()/100;
               QMessageBox::information(this,tr("tzp"),QString::number(initarea));
               ui->lineEdit->setText(QString::number(initarea));

            }
        }
    }
}

float MainWindow::next()
{
     this->strategy->nextPackingCommand();
     this->strategy->compPackingLayout(this->layout);
     //update();
     return this->layout.compArea()/100;
}

void MainWindow::find()
{

    float area=layout.compArea()/100;
    float minArea=area;
    Layout minLayout=this->layout;   
    T=this->setDialog.T;
    I=this->setDialog.I;
    rate=this->setDialog.rate;
    int i1=0;
    int i=100;
    while(i1++<I)
    {
        for(int j=0;j<i;j++)
        {
            float newArea=next();
            float c=newArea-area;
            if(c<0)
            {
                area=newArea;
                if(area<minArea)
                {
                    minArea=area;
                    minLayout=this->layout;
                }
                ui->lineEdit->setText(QString::number(area));
                repaint();
            }
            else
            {
                float tmp= (rand()%100)*0.01;
                int a=-c/T;
                if(tmp<pow(2.71828,a))
                {
                    area=newArea;
                    //ui->lineEdit->setText(QString::number(area));
                    //repaint();
                }
            }
        }
        T=rate*T;
        i=1.2*i;
    }

    this->layout=minLayout;
    ui->lineEdit->setText(QString::number(minArea));
    update();

}

void MainWindow::on_action_2_triggered()
{

    setDialog.show();
}

void MainWindow::mousePressEvent(QMouseEvent *ev)
{
   // Point mousePoint;
    initPoint=ev->pos();
    int x=initPoint.x();
    int y=initPoint.y();
    Rect tmpRect;
    for(int i=0;i<num;i++)
    {
        tmpRect=this->layout.getRect(i);
        int xx=tmpRect.lb.x+20;
        int yy=tmpRect.lb.y+60;
        int width=tmpRect.width;
        int height=tmpRect.height;
        if((x-xx)<width&&(x-xx)>0&&(y-yy)<height&&(y-yy)>0)
        {
            if(rectClicked!=i)
                rectClicked=i;
            else rectClicked=-1;

            repaint();
            break;
        }
    }
    //QMessageBox::information(this,tr("tzp"),QString::number(rectClicked));
}
void MainWindow::mouseMoveEvent(QMouseEvent *ev)
{
    if(rectClicked<0) return;
    QPoint endPoint=ev->pos();
    int cx=endPoint.x()-initPoint.x();
    int cy=endPoint.y()-initPoint.y();
    //Rect *tmpRect=new Rect();
    //tmpRect=&this->layout.getRect(rectClicked);
    if((this->layout.getRect(rectClicked).lb.x+20+cx)>0&&
       (this->layout.getRect(rectClicked).lb.x+20+cx+this->layout.getRect(rectClicked).width<(this->width())&&
       (this->layout.getRect(rectClicked).lb.y+15+cy)>0&&
       (this->layout.getRect(rectClicked).lb.y+60+cy+this->layout.getRect(rectClicked).height)<this->height()))
    {
       this->layout.getRect(rectClicked).lb.x+=cx;
       this->layout.getRect(rectClicked).lb.y+=cy;
       initPoint=endPoint;
    }
    else
    {
        QMessageBox::warning(this,tr("tzp"),"OUT!");
    }

    repaint();

}

void MainWindow::mouseReleaseEvent(QMouseEvent *ev)
{
    //strategy->initialPacking(this->layout);
    repaint();
}

void MainWindow::on_action_3_triggered()
{
    if(num<=0)
    {
        QMessageBox::warning(this,tr("tzp"),tr("没有元素!"));
        return ;
    }

    find();
}

void MainWindow::on_action_4_triggered()
{
    if(this->rectClicked<0)
    {
        QMessageBox::warning(this,tr("tzp"),tr("请选择元素！"));
    }
    else
    {
        this->layout.getRects().erase(layout.getRects().begin()+rectClicked);
        num--;
        rectClicked=-1;
        strategy->initialPacking(this->layout);
        repaint();
    }
}

void MainWindow::on_action_5_triggered()
{
    setDialog_2.show();
}

void MainWindow::on_add()
{
    Rect newRect;
    newRect.width=this->setDialog_2.width*10;
    newRect.height=this->setDialog_2.height*10;
    this->layout.getRects().push_back(newRect);
    num++;
    strategy->initialPacking(this->layout);
    repaint();

}
