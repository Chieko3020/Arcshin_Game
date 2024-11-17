#include "setting.h"
#include "ui_setting.h"
#include "mainwindow.h"

int gametime=100;//初始化游戏限时
int Speed =5;//初始化游戏下落速度
int speedpd=1;//初始化游戏下落加速度

setting::setting(QWidget *parent)//构造函数
    : QWidget(parent)
    , ui(new Ui::setting)
{
    ui->setupUi(this);//创建设置窗口
    ui->timebox->setRange(0,300);//设置参数
    ui->timebox->setSingleStep(10);
    ui->timebox->setSuffix(" s");
    ui->timebox->setValue(gametime);
    ui->timebox->setWrapping(true);
    ui->speedbox->setRange(1,10);
    ui->speedbox->setSingleStep(1);
    ui->speedbox->setValue((60-Speed)/10);
    ui->speedbox->setPrefix("  ");
    ui->speedbox->setWrapping(true);
    ui->accbox->setRange(1,5);
    ui->accbox->setSingleStep(1);
    ui->accbox->setValue(speedpd);
    ui->accbox->setPrefix("  x");
    ui->accbox->setWrapping(true);
}

setting::~setting()//析构函数
{
    delete ui;
}

void setting::on_timebox_valueChanged()//游戏时间输入框的槽函数
{
    gametime=ui->timebox->value();
}


void setting::on_speedbox_valueChanged()//原石和星琼下落速度的槽函数
{
    Speed=ui->speedbox->value();
}


void setting::on_accbox_valueChanged()//原石和星琼下落加速度的槽函数
{
    speedpd=ui->accbox->value();
}
