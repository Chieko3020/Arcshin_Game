/*游戏主界面所属的帮助子界面头文件*/
#ifndef HELP_H
#define HELP_H
#include <QWidget>

namespace Ui
{
    class help;
}

class help : public QWidget
{
    Q_OBJECT

public:
    explicit help(QWidget *parent = nullptr);//显式构造函数
    ~help();//析构函数

private:
    Ui::help *ui;//帮助界面窗口指针
};
#endif // HELP_H
