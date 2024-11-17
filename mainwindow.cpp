#include "mainwindow.h"
#include "gamewindow.h"
#include "help.h"
#include "setting.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QApplication>

bool state=0;//游戏运行状态
bool settle=0;//游戏结算状态

MainWindow::MainWindow(QWidget *parent)//构造函数
    : QMainWindow(parent)
    , ui(new Ui::Arcshin)
{
    ui->setupUi(this);//创建主窗口
    ui->volume->setIcon(QPixmap(":/res/volume.png"));//设置音乐按钮播放图标
    ui->volume->setIconSize(QSize(60,60));//设置音乐按钮大小
    audio();//播放音乐
    connect(ui->quit, SIGNAL(clicked()), qApp, SLOT(quit()) );//关联退出按钮和关闭程序
    QCursor* mycursor= new QCursor(QPixmap(":/res/cursor.png"),-1,-1);//设置鼠标样式
    this->setCursor(*mycursor);//应用鼠标样式
}

MainWindow::~MainWindow()//析构函数
{
    delete ui;
}

void MainWindow::audio()//播放音乐
{
    m_player->setAudioOutput(m_audioOutput);
    m_player->setSource(QUrl("qrc:/res/bgm.mp3"));
    m_player->setLoops(-1);//无限循环
    m_player->play();
}

void MainWindow::on_play_clicked()//开始游戏按钮的槽函数
{
    if((!state)&&(!settle))
    {
        gamewindow *game = new gamewindow;//跳转游戏界面
        game->setAttribute(Qt::WA_DeleteOnClose);//关闭即销毁窗口
        game->setAttribute(Qt::WA_QuitOnClose,false);//仅主窗口关闭可结束进程
        connect(game,SIGNAL(bgmpause()),this,SLOT(musicpause()));//关联游戏暂停的音乐状态信号与音乐播放控制函数
        connect(game,SIGNAL(bgmplay()),this,SLOT(musicplay()));
        game->show();
        state=1;
    }
    else
    {
        QMessageBox msgbox;
        msgbox.setText("You cannot start another game until the current game is settled");
        msgbox.exec();
        return;
    }
}

void MainWindow::on_rule_clicked()//游戏规则参数设置按钮的槽函数
{

    if(!state)
    {
        setting *s= new setting;//跳转设置界面
        s->setAttribute(Qt::WA_DeleteOnClose);//关闭即销毁窗口
        s->setAttribute(Qt::WA_QuitOnClose,false);//仅主窗口关闭可结束进程
        s->setWindowModality(Qt::ApplicationModal);//模态 在调整难度完成前不可进行其他操作
        s->show();
    }
    else
    {
        QMessageBox msgbox;
        msgbox.setText("You cannot adjust difficulty until the current game is settled");
        msgbox.exec();
        return;
    }
}

void MainWindow::on_volume_clicked()//音乐播放与静音按钮的槽函数
{
    if(bgm)
    {
        m_player->pause();
        ui->volume->setIcon(QPixmap(":/res/volume_close.png"));//设置音乐按钮静音图标
        bgm=false;
    }
    else
    {
        m_player->play();
        ui->volume->setIcon(QPixmap(":/res/volume.png"));//设置音乐按钮播放图标
        bgm=true;
    }
}

void MainWindow::on_help_clicked()//帮助按钮的槽函数
{
    help* h=new help;//跳转帮助界面
    h->setAttribute(Qt::WA_DeleteOnClose);//关闭即销毁窗口
    h->setAttribute(Qt::WA_QuitOnClose,false);//仅主窗口关闭可结束进程
    h->setWindowModality(Qt::ApplicationModal);//模态 在调整难度完成前不可进行其他操作
    h->show();
}

void MainWindow::musicplay()
{
    if(bgm)
        m_player->play();
}

void MainWindow::musicpause()
{
    if(bgm)
        m_player->pause();
}

void MainWindow::closeEvent(QCloseEvent *event)//重载关闭事件
{
    QMessageBox msgBox;
    msgBox.setText("Are you really going to quit ?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if(msgBox.exec()==QMessageBox::No)
        event->ignore();
}
