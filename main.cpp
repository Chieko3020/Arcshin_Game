#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);//创建进程
    MainWindow w;//创建主窗口
    w.show();
    return a.exec();
}
