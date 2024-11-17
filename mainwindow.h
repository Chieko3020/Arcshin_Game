/*游戏开始窗口*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
QT_BEGIN_NAMESPACE

extern int Speed;//原石和星琼的下落速度
extern int speedpd;//原始和星琼的下落加速度
extern int gametime;//游戏限时
extern bool state;//游戏运行状态
extern bool settle;//游戏结算状态

namespace Ui
{
    class Arcshin;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);//显式构造函数
    ~MainWindow();//析构函数
    void audio();//音乐初始化
    void closeEvent(QCloseEvent *event);//重载关闭事件
    bool bgm=1;//音乐播放状态
    int gametime=100;//游戏限时

private:
    Ui::Arcshin *ui;//主界面窗口指针
    QMediaPlayer *m_player =new QMediaPlayer;//播放音乐
    QAudioOutput *m_audioOutput = new QAudioOutput;//音频输出

private slots:
    void on_play_clicked();//开始游戏按钮的槽函数
    void on_rule_clicked();//游戏规则参数设置按钮的槽函数
    void on_volume_clicked();//音乐播放与静音按钮的槽函数
    void on_help_clicked();//帮助按钮的槽函数
    void musicplay();//来自游戏窗口的播放音乐信号的槽函数
    void musicpause();//来自游戏窗口的暂停音乐信号的槽函数
};
#endif // MAINWINDOW_H
