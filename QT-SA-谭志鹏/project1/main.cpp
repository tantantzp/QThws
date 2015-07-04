#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QTextCodec>
#include <ctime>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QTextCodec::setCodecForTr(QTextCodec::codecForName("gb18030"));

    srand(unsigned(time(0)));

    MainWindow w;

    w.show();

    return a.exec();
}
