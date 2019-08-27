#include "widget.h"
#include "ui_widget.h"
#include "admin.h"
#include<fstream>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->Label_5->setStyleSheet("color:red;");

    connect(ui->ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(change_iden()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(show_pass()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(register_check()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(login_check()));


}

Widget::~Widget()
{
    delete ui;
    setAttribute(Qt::WA_DeleteOnClose);
}

void Widget::loginshow(){
    this->show();
}

void Widget::show_pass(){//显示300ms密码


    if(ui->pushButton_2->text()=="show"){
        ui->LineEdit_2->setEchoMode(QLineEdit::Normal);
        ui->pushButton_2->setText("hide");
        sleep(300);
        ui->LineEdit_2->setEchoMode(QLineEdit::Password);
        ui->pushButton_2->setText("show");
    }
    else {
        ui->LineEdit_2->setEchoMode(QLineEdit::Password);
        ui->pushButton_2->setText("show");
    }

}

void Widget::login_check(){//登陆检测权限

    if(ui->ComboBox->currentIndex()==0){//管理员登陆

        string acc=(ui->LineEdit->text()).toStdString();
        string pas=(ui->LineEdit_2->text()).toStdString();
        string dat=(ui->LineEdit_3->text()).toStdString();
        Admin got(acc,pas,dat);

        if(!(pas==""||acc==""||dat=="")){

                if(got.search_all()){
                    close();
                    ui->LineEdit->setText("");
                    ui->LineEdit_2->setText("");
                    ui->LineEdit_3->setText("");
                    emit send_filename(dat);
                    emit loginquit();
                }

                else {
                    ui->Label_5->setText("数据库、账号或密码不匹配！");
                    sleep(700);
                    ui->Label_5->setText("");
                }
        }

        else {
            ui->Label_5->setText("请输入正确的账号或密码！");
            sleep(700);
            ui->Label_5->setText("");
        }

    }


    else {//访客登陆

        string dat=(ui->LineEdit_3->text()).toStdString();
        using namespace std;
        fstream got(dat);

        if(!got){
            ui->Label_5->setText("没有找到该数据库！");
            sleep(700);
            ui->Label_5->setText("");
            got.close();
        }

        else {
            got.close();
            //close();
            /*进入查询功能*/
            ui->LineEdit->setText("");
            ui->LineEdit_2->setText("");
            ui->LineEdit_3->setText("");
            emit send_filename(dat);
            emit visitorcomes();
            this->close();
        }

    }



}

void Widget::register_check(){//注册合法性检查

    using namespace std;
    string acc=(ui->LineEdit->text()).toStdString();
    string pas=(ui->LineEdit_2->text()).toStdString();
    string dat=(ui->LineEdit_3->text()).toStdString();
    if(acc==""||pas==""||dat==""){
        ui->Label_5->setText("请输入正确的格式!");
        sleep(1000);
        ui->Label_5->setText("");
    }

    else {
        Admin a(acc,pas,dat);
        if(!a.search_dat()){
            if(a.down_in_file(dat)){
                ui->Label_5->setText("数据库创建成功！");
            }
            else
                ui->Label_5->setText("数据库创建失败！");

            sleep(2000);
            ui->Label_5->setText("");
            }
        else {
            ui->Label_5->setText("已注册过的数据库用户名或密码！");
            sleep(2000);
            ui->Label_5->setText("");
        }
    }

}

void Widget::change_iden(){//改变按钮状态

    if(ui->ComboBox->currentIndex()==1)
    {
        ui->LineEdit->setText("");
        ui->LineEdit_2->setText("");
        ui->LineEdit_3->setText("");
        ui->LineEdit->setEnabled(false);
        ui->LineEdit_2->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->Label_2->setEnabled(false);
        ui->Label_3->setEnabled(false);
    }
    else {
        ui->LineEdit->setText("");
        ui->LineEdit_2->setText("");
        ui->LineEdit_3->setText("");
        ui->LineEdit->setEnabled(true);
        ui->LineEdit_2->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->Label_2->setEnabled(true);
        ui->Label_3->setEnabled(true);
    }

}
