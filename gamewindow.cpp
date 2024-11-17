#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "score.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QPixmap>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QLabel>
#include <QTime>

int i=0;//初始化计时响应器
int counter=0;//初始化计分器
int gemstones=0;//初始化原石计数器

gamewindow::gamewindow(QWidget *parent)//构造函数
    : QWidget(parent)
    , ui(new Ui::gamewindow)
{
    ui->setupUi(this);//创建游戏窗口
    Timer.setInterval(10);//原石和星琼出现计时器的计时响应间隔 10毫秒
    timer.setInterval(1000);//游戏限时计时器的计时响应间隔 1秒
    recorder = 0;//初始化原石和星琼的出现间隔计时响应器
    srand((unsigned int)time(NULL));//随机数种子 用于控制原石和星琼出现初始x坐标
    ui->time_number->setAlignment(Qt::AlignCenter);//控制计时器显示屏文字居中
    ui->count->setAlignment(Qt::AlignCenter);//控制计数器显示屏文字居中
    ui->pause->hide();//隐藏暂停图片
    QCursor* mycursor= new QCursor(QPixmap(":/res/cursor.png"),-1,-1);//设置鼠标样式
    this->setCursor(*mycursor);//应用鼠标样式
    play();//启动游戏
}

gamewindow::~gamewindow()//析构函数
{
    delete ui;
}

void gamewindow::mouseMoveEvent(QMouseEvent *event)//重载鼠标移动事件
{
    int x = event->position().x() - mhikari.Rect.width()*0.5;//坐标为当前鼠标坐标与人物矩形框一半之差
    int y = event->position().y() - mhikari.Rect.height()*0.5;
    if(x <= 0 )//游戏界面边界检测
    {
        x = 0;
    }
    if(x >= 512  - mhikari.Rect.width())
    {
        x = 512 - mhikari.Rect.width();
    }
    if(y <= 40)
    {
        y = 40;
    }
    if(y >= 768 - mhikari.Rect.height())
    {
        y = 768 - mhikari.Rect.height();
    }
    mhikari.update(x,y);
}

void gamewindow::keyPressEvent(QKeyEvent *event)//重载键盘响应事件
{
    if(event->key()==Qt::Key_Escape)//按下Esc退出并返回
    {
        state=0;
        this->close();
    }
    if(event->key()==Qt::Key_E)//按下E结算
    {
        i=gametime;
    }
    if(event->key()==Qt::Key_P&&!pause)//按下P暂停或继续
    {
        Timer.stop();//暂停原石和星琼的位置更新
        timer.stop();//暂停倒计时
        pause=1;//暂停音乐
        bgmpause();
        ui->pause->show();
    }
    else if(event->key()==Qt::Key_P&&pause)
    {
        Timer.start();//恢复原石和星琼的位置更新
        timer.start();//恢复倒计时
        pause=0;//续播音乐
        bgmplay();
        ui->pause->hide();
    }
}

void gamewindow::closeEvent(QCloseEvent *)//重载关闭事件
{
    state=0;
    this->close();
}

void gamewindow::paintEvent(QPaintEvent *)//重载绘图事件
{
    QPainter painter(this);//绘图对象
    painter.drawPixmap(0,0,QPixmap(":/res/bg.png"));//背景
    painter.drawPixmap(mhikari.X,mhikari.Y,mhikari.hkr);//人物
    for(int i = 0 ; i< 2000;i++)//原石和星琼
    {
        if(mgemstones[i].Free == false)
        {
            painter.drawPixmap(mgemstones[i].X,mgemstones[i].Y,mgemstones[i].gs);
        }
    }
}

void gamewindow::gemstonets()//控制原石和星琼出现在场景中
{
    recorder++;//计时响应器
    if(recorder < 30)//300毫秒出现一次
    {
        return;
    }
    recorder = 0;
    for(int i = 0 ; i< 2000;i++)
    {
        if(mgemstones[i].Free)
        {
            mgemstones[i].Free = false;//在场状态
            mgemstones[i].X = rand() % (512 - mgemstones[i].Rect.width());//初始x坐标为当前随机坐标与原石或星琼矩形框一半之差
            mgemstones[i].Y = -mgemstones[i].Rect.height();//初始y坐标为场外原石或星琼矩形框一半
            if(mgemstones[i].type==0)
                gemstones++;
            break;
        }
    }
}

void gamewindow::play()//启动游戏
{
    i=0;//初始化计时响应器
    counter=0;//初始化计分器
    gemstones=0;//初始化原石计数器
    Timer.start();
    timer.start();
    ui->time_number->setNum(gametime);//显示倒计时
    connect(&timer,SIGNAL(timeout()),this,SLOT(onTimeout()));//关联倒计时与响应器
    connect(&Timer,&QTimer::timeout,[=]()//关联计时器与游戏各函数和碰撞检测
                                           //[=](){}为lamda表达式 定义一个函数体为4个函数的匿名槽函数
    {
        gemstonets();//控制原石和星琼出现在场景中
        judgeup();//更新原石和星琼的位置的判断函数
        update();//绘图事件的更新函数
        collisiondetection();//控制人物获取原石和星琼时的碰撞检测与分数计算
    }
            );
}

void gamewindow::judgeup()//更新原石和星琼的位置的判断函数
{
    for(int i = 0 ; i< 2000;i++)
    {
        if(mgemstones[i].Free == false)
        {
            mgemstones[i].update();
        }
    }
}

void gamewindow::collisiondetection()//控制人物获取原石和星琼时的碰撞检测与分数计算
{

    for(int i = 0 ;i < 2000;i++)
    {
        if(mgemstones[i].Free)
        {
            continue;
        }
        if(mgemstones[i].Rect.intersects(mhikari.Rect))//原石或星琼与人物二者矩形框相交
        {
            mgemstones[i].Free = true;//获取原石或星琼
            if(mgemstones[i].type)//星琼扣分 原石加分
                counter--;
            else
                counter++;
            if(counter<0)//计数器非负
                counter=0;
            ui->count->setNum(counter);
        }
    }
}
void gamewindow::onTimeout()//响应倒计时和结束跳转结算页面的槽函数
{
    if(i==gametime)
    {
        state=0;
        settle=1;
        timer.stop();
        Timer.stop();
        score* sc=new score;//跳转结算界面
        sc->setAttribute(Qt::WA_DeleteOnClose);//关闭即销毁窗口
        sc->setAttribute(Qt::WA_QuitOnClose,false);//仅主窗口关闭可结束进程
        sc->show();
        this->close();//关闭游戏界面
    }
    i++;//每1秒响应一次直至倒计时结束
    ui->time_number->setNum(gametime-i);
}
