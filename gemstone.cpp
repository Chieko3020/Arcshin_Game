#include "gemstone.h"
#include "mainwindow.h"
#include "gamewindow.h"
#include <QPainter>

int imgflag=1;//控制原石与星琼交替出现

gemstone::gemstone()
{
    if(imgflag)//原石
    {
        gs.load(":/res/gs.png");
        type=0;
        imgflag=0;
    }
    else if(!imgflag)//星琼
    {
        gs.load(":/res/ss.png");
        type=1;
        imgflag=1;
    }
    X = 0;//初始化坐标及在场状态
    Y = 0;
    Free = true;
    Rect.setWidth(gs.width());//原石或星琼矩形框
    Rect.setHeight(gs.height());
    Rect.moveTo(X,Y);
}

void gemstone::update()//设置原石和星琼的位置
{
    if(Free)//不在场
    {
        return;
    }
    Y += Speed+i/(speedpd*-10+60);//在场
    Rect.moveTo(X,Y);
    if(Y >= 768 + Rect.height())//出场
    {
        Free = true;
    }
}
