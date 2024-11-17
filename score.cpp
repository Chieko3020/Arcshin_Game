#include "score.h"
#include "ui_score.h"
#include "gamewindow.h"
#include "mainwindow.h"
#include <QMessagebox>

score::score(QWidget *parent)//构造函数
    : QWidget(parent)
    , ui(new Ui::score)
{
    ui->setupUi(this);//创建结算窗口
    QCursor* mycursor= new QCursor(QPixmap(":/res/cursor.png"),-1,-1);//设置鼠标样式
    this->setCursor(*mycursor);//应用鼠标样式
    changeimg();//依据分数评级更换背景图片
    setcnt();//由获取的原石数量设置桃子数量
    initlist();//初始化链表
}

score::~score()
{
    destroylist();
    delete ui;
}

void score::changeimg()//依据分数评级更换背景图片
{
    if(counter>=0&&counter<=gemstones*0.5)//C
    {
        ui->bg->setPixmap(QPixmap(":/res/rankc.png"));
        ui->bg->setScaledContents(true);//图片自适应大小
        ui->rankimg->setPixmap(QPixmap(":/res/C.png"));
        ui->rankimg->setScaledContents(true);
    }

    else if(counter>gemstones*0.5&&counter<=gemstones*0.8)//B
    {
        ui->bg->setPixmap(QPixmap(":/res/rankb.png"));
        ui->bg->setScaledContents(true);
        ui->rankimg->setPixmap(QPixmap(":/res/B.png"));
        ui->rankimg->setScaledContents(true);
    }
    else if(counter>gemstones*0.8)//A
    {
        ui->bg->setPixmap(QPixmap(":/res/ranka.png"));
        ui->bg->setScaledContents(true);
        ui->rankimg->setPixmap(QPixmap(":/res/A.png"));
        ui->rankimg->setScaledContents(true);
    }
}

void score::setcnt()//由获取的原石数量设置桃子数量
{
    ui->gscnt->setNum(counter);
    ui->peachcnt->setNum(counter*3);
    ui->count->setNum(counter*3);
}

void score::initlist()//初始化链表
{
    l=new lnode;
    l->data=0;
    l->next=nullptr;
}

bool score::listimpty()//链表判空
{
    if(l->next==nullptr)
        return true;
    else
        return false;
}

void score::destroylist()//销毁链表
{
    if(!listimpty())
    {
        while(l)
        {
            lnode* temp=l->next;
            delete l;
            l=temp;
        }
    }
    else
        return;
}

int score::getdayrecursive(int cnt)//以递归方式计算桃子可食用天数
{
    int temp=cnt;
    if(temp>1)
    {
        if(temp%2)//奇偶判断下一天剩余数量 向上取整
            temp=temp/2;
        else
            temp=temp/2-1;
        if(temp==0)//最后一天必定剩余1个
            temp=1;
        return getdayrecursive(temp)+1;
    }
    else
        return 0;
}

int score::getdayarray(int cnt,int peach[])//利用数组计算桃子可食用天数
{
    peach[0]=cnt;
    int i=1;
    while(peach[i-1]>1)
    {
        if(peach[i-1]%2)//奇偶判断下一天剩余数量 向上取整
            peach[i]=peach[i-1]/2;
        else
            peach[i]=peach[i-1]/2-1;
        if(peach[i]==0)//最后一天必定剩余1个
            peach[i]=1;
        i++;
    }
    return i-1;
}

int score::getdaylinklist(int cnt,linklist &l)//利用链表计算桃子可食用天数
{
    int temp=cnt;
    l->data=temp;
    lnode* r=l;
    int day=0;
    while(temp>1)
    {
        day++;
        lnode* p=new lnode;
        if(temp%2)//奇偶判断下一天剩余数量 向上取整
            temp=temp/2;
        else
            temp=temp/2-1;
        if(temp==0)//最后一天必定剩余1个
            temp=1;
        p->data=temp;
        p->next=r->next;
        r->next=p;
        r=r->next;
    }
    return day;
}

int score::getpeacharray(int day,int peach[])//利用数组查询某一天桃子剩余数量
{
    return peach[day];
}

int score::getpeachlinklist(int day,linklist &l)//利用链表查询某一天桃子剩余数量
{
    if(!listimpty())
    {
        lnode* q=l;
        for(int i=1;i<=day;i++)
        {
            q=q->next;
        }
        return q->data;
    }
    else
        return 0;
}

void score::on_againbtn_clicked()//再次游玩按钮的槽函数
{
    state=1;
    settle=0;
    gamewindow* g=new gamewindow;//跳转游戏界面
    g->show();
    g->setAttribute(Qt::WA_DeleteOnClose);//关闭即销毁窗口
    g->setAttribute(Qt::WA_QuitOnClose,false);//仅主窗口关闭可结束进程
    this->close();
}

void score::on_exitbtn_clicked()//退出并返回主界面按钮的槽函数
{
    state=0;
    settle=0;
    this->close();//关闭结算界面
}

void score::on_cmbtn_clicked()//切换计算天数方法按钮的槽函数
{
    if((flagm%3)==1)
    {
        ui->cmethod->setText("(Array)");
        DAY=getdayarray(counter*3,peach);
        ui->days->setNum(DAY);//显示天数
        flagm++;
        arrayq=true;
    }
    else if((flagm%3)==2)
    {
;
        ui->cmethod->setText("(Linklist)");
        DAY=getdaylinklist(counter*3,l);
        ui->days->setNum(DAY);
        flagm++;
        linklistq=true;
    }
    else if((flagm%3)==0)
    {
        ui->cmethod->setText("(Recursive)");
        DAY=getdayrecursive(counter*3);
        ui->days->setNum(DAY);
        flagm++;
    }
}

void score::on_qmbtn_clicked()//切换查询桃子数量方法按钮的槽函数
{
    qmbtn=1;
    if(flagq)
    {
        ui->qmethod->setText("(Array)");//显示桃子数量
        flagq=0;
    }
    else if(!flagq)
    {
        ui->qmethod->setText("(Linklist)");
        flagq=1;
    }
}

void score::on_help_clicked()//使用帮助提示按钮的槽函数
{
    QMessageBox msgbox;
    msgbox.setText("Choose calculate method first,\nthen choose query method and press Enter\nafter enter the day in textbox you want to query.");
    msgbox.exec();
}

void score::on_dayquery_returnPressed()//查询天数输入框的槽函数
{
    if(!qmbtn)
    {
        QMessageBox msgbox;
        msgbox.setText("You must calculate days and choose the query method first.");
        msgbox.exec();
        return;
    }
    if(ui->dayquery->text().toInt()>DAY||ui->dayquery->text().toInt()<=0)
    {
        QMessageBox msgbox;
        msgbox.setText("Invalid input.");
        msgbox.exec();
        return;
    }
    dayq=ui->dayquery->text().toInt();
    if(!flagq)
    {
        if(arrayq)//判断是否已利用数组计算天数
            ui->peachquery->setNum(getpeacharray(dayq,peach));
        else
        {
            QMessageBox msgbox;
            msgbox.setText("You must calculate days and choose the query method first.");
            msgbox.exec();
            return;
        }
    }
    if(flagq)
    {
        if(linklistq)//判断是否已利用链表计算天数
            ui->peachquery->setNum(getpeachlinklist(dayq,l));
        else
        {
            QMessageBox msgbox;
            msgbox.setText("You must calculate days and choose the query method first.");
            msgbox.exec();
            return;
        }
    }
    return;
}
