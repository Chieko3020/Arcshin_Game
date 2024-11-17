/*游戏人物头文件*/
#ifndef HIKARI_H
#define HIKARI_H
#include <QPixmap>

class hikari
{
public:
    hikari();//构造函数
    void update(int x, int y);//设置人物位置
    QPixmap hkr;//人物图片绘图对象
    QRect Rect;//人物的矩形边框
    int X;//人物的x坐标
    int Y;//人物的y坐标
};
#endif // HIKARI_H
