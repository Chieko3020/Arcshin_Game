/*结算界面头文件*/
#ifndef SCORE_H
#define SCORE_H
#include <QWidget>

class lnode//结点
{
public:
    int data;//数据域
    class lnode* next;//指针域
};
typedef lnode* linklist;//头节点

namespace Ui
{
    class score;
}

class score : public QWidget
{
    Q_OBJECT

public:
    explicit score(QWidget *parent = nullptr);//显式构造函数
    ~score();//析构函数
    void changeimg();//依据分数评级更换背景图片
    void setcnt();//由获取的原石数量设置桃子数量
    void initlist();//初始化链表
    bool listimpty();//链表判空
    void destroylist();//销毁链表
    int getdayrecursive(int cnt);//以递归方式计算桃子可食用天数
    int getdayarray(int cnt,int peach[]);//利用数组计算桃子可食用天数
    int getdaylinklist(int cnt,linklist &l);//利用链表计算桃子可食用天数
    int getpeacharray(int day,int peach[]);//利用数组查询某一天桃子剩余数量
    int getpeachlinklist(int day,linklist &l);//利用链表查询某一天桃子剩余数量
    int DAY=0;//天数
    int dayq=1;//查询天数
    int flagm=1;//计算方法
    bool flagq=1;//查询方法
    bool qmbtn=0;//查询方法切换状态
    bool arrayq=0;//数组计算状态
    bool linklistq=0;//链表计算状态
    int peach[12]={0};//桃子数组
    linklist l;//桃子链表


private:
    Ui::score *ui;//结算界面窗口指针

private slots:
    void on_againbtn_clicked();//再次游玩按钮的槽函数
    void on_exitbtn_clicked();//退出并返回主界面按钮的槽函数
    void on_cmbtn_clicked();//切换计算天数方法按钮的槽函数
    void on_qmbtn_clicked();//切换查询桃子数量方法按钮的槽函数
    void on_help_clicked();//使用帮助提示按钮的槽函数
    void on_dayquery_returnPressed();//查询天数输入框的槽函数
};
#endif // SCORE_H
