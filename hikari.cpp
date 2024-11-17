#include "hikari.h"

hikari::hikari()//构造函数
{
    hkr.load(":/res/hkr.png");
    X = 256-hkr.width()*0.5;//初始化坐标为场景底部中央
    Y = 768-hkr.height();
    Rect.setWidth(hkr.width());//人物矩形框
    Rect.setHeight(hkr.height());
    Rect.moveTo(X,Y);
}

void hikari::update(int x,int y)//设置人物位置
{
    X = x;
    Y = y;
    Rect.moveTo(X,Y);
}
