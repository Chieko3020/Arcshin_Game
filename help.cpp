#include "help.h"
#include "ui_help.h"

help::help(QWidget *parent)//构造函数
    : QWidget(parent)
    , ui(new Ui::help)
{
    ui->setupUi(this);//创建帮助窗口
    QCursor* mycursor= new QCursor(QPixmap(":/res/cursor.png"),-1,-1);//设置鼠标样式
    this->setCursor(*mycursor);//应用鼠标样式
}

help::~help()//析构函数
{
    delete ui;
}
