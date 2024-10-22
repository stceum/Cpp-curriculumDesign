#ifndef ADMIN_H
#define ADMIN_H

#include<iostream>
#include<fstream>
using namespace std;
class MainWindow;

//管理员可能需要注册，或者需要登陆
class Admin{
public:
    friend class MainWindow;
    Admin(string &acc_,string &pas_,string &dat_):acc(acc_),pas(pas_),dat(dat_){}
    bool down_in_file(string &filename);
    bool search_dat();//从文件中search该对象
    string search_low();
    bool search_all();
    bool del_data();
    bool change_paswd(string new_passwd);
private:
    string acc,pas,dat;
};


#endif // ADMIN_H
