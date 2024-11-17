/*游戏界面头文件*/
#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include "gemstone.h"
#include "hikari.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QWidget>
#include <QTimer>

extern int i;//控制原石与星琼出现的计时响应器
extern int counter;//计分器
extern int gemstones;//出现的原石计数器，用于评级

namespace Ui
{
    class gamewindow;
}

class gamewindow : public QWidget
{
    Q_OBJECT

public:
    explicit gamewindow(QWidget *parent = nullptr);//显式构造函数
    ~gamewindow();//析构函数
    void mouseMoveEvent(QMouseEvent *event);//重载鼠标移动事件 用于控制人物移动
    void keyPressEvent(QKeyEvent *event);//重载键盘响应事件 用于P键暂停或继续游戏以及E键结算
    void closeEvent(QCloseEvent *event);//重载关闭事件
    void paintEvent(QPaintEvent *event);//重载绘图事件 用于绘制游戏背景，人物以及原石和星琼
    void gemstonets();//控制原石和星琼出现在场景中
    void play();//启动游戏
    void judgeup();//更新原石和星琼的位置的判断函数
    void collisiondetection();//控制人物获取原石和星琼时的碰撞检测与分数计算
    hikari mhikari;//人物
    gemstone mgemstones[2000];//原石和星琼
    int recorder;//原石和星琼的出现间隔计时响应器
    bool pause=0;//游戏暂停状态
    QTimer Timer;//控制原石和星琼出现的计时器
    QTimer timer;//控制游戏限时的计时器

private:
    Ui::gamewindow *ui;//游戏界面窗口指针

private slots:
    void onTimeout();//响应倒计时和结束跳转结算页面的槽函数

signals:
    void bgmpause();//控制游戏背景音乐暂停的信号函数 由主函数接收
    void bgmplay();//控制游戏背景音乐续播的信号函数 由主函数接收
};
#endif // GAMEWINDOW_H
