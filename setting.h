/*游戏规则参数界面的头文件*/
#ifndef SETTING_H
#define SETTING_H
#include <QWidget>

namespace Ui
{
    class setting;
}

class setting : public QWidget
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = nullptr);//显式构造函数
    ~setting();//析构函数

private slots:
    void on_timebox_valueChanged();//游戏时间输入框的槽函数
    void on_speedbox_valueChanged();//原石和星琼下落速度的槽函数
    void on_accbox_valueChanged();//原石和星琼下落加速度的槽函数

private:
    Ui::setting *ui;//游戏规则设置界面窗口指针
};
#endif // SETTING_H
