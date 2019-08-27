#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "delay.h"
#include<iostream>
#include"admin.h"


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();


private slots:

    void loginshow();

    void login_check();//与登陆按钮相连

    void register_check();//与注册按钮相连

    void show_pass();//显示密码

    void change_iden();//变换身份


signals:
    void loginquit();//登陆成功
    void visitorcomes();
    void send_filename(string);//发送待编辑文件名

private:
    Ui::Widget *ui;


};

#endif // WIDGET_H
