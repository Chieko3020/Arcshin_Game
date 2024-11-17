/*原石和星琼头文件*/
#ifndef GEMSTONE_H
#define GEMSTONE_H
#include <QPixmap>

class gemstone
{
public:
    gemstone();
    void update();//设置原石和星琼的位置
    QPixmap gs;//原石和星琼图片绘图对象
    QRect Rect;//原石和星琼的矩形边框
    int X;//原石和星琼的x坐标
    int Y;//原石和星琼的y坐标
    int type;//控制原石与星琼二者出现的类型 原石为0 星琼为1
    bool Free;//原石和星琼在场状态 在场为false 已被获取或出场为true
};
#endif // GEMSTONE_H
