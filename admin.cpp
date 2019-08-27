#include"admin.h"
#include"enc_doc.h"

//将账户文件写到.acc文件中
bool Admin::down_in_file(string &filename){
    fstream account;
    account.open("data.acc",ios_base::in);
    if(account){
        account.close();
        account.open("data.acc",ios_base::in|ios_base::app);
    }
    else {
        account.close();
        account.open("data.acc",ios_base::out);
    }
    if(account<<"account="<<acc<<";"<<"password="<<Encrypt(pas)<<";"<<"datatitle="<<dat<<";")
    {
        account.close();
        account.open(filename,ios_base::out);
        account.close();
        return 1;
    }
    else {
        return 0;
    }
}

bool Admin::search_dat(){//0代表没有找到
    fstream account;
    account.open("data.acc",ios_base::in);
    if(!account) {
        account.close();
        return 0;
    }
    string acc_,pas_,dat_,tem;
    int status=0;
    while(!account.eof()){
        getline(account,tem,'=');
        if(tem=="account")getline(account,acc_,';');
        else if (tem=="password") {
            getline(account,pas_,';');
            Decode(pas_);
        }
        else getline(account,dat_,';');
        if(dat_==dat)
           status=1;
    }
    account.close();
    return  status;
}

bool Admin::search_all(){
    fstream account;
    account.open("data.acc",ios_base::in);
    if(!account) {
        account.close();
        return 0;
    }
    string acc_,pas_,dat_,tem;
    int status=0;
    while(!account.eof()){
        getline(account,tem,'=');
        if(tem=="account")getline(account,acc_,';');
        else if (tem=="password") {
            getline(account,pas_,';');
            Decode(pas_);
        }
        else getline(account,dat_,';');
        if(dat_==dat&&acc_==acc&&pas_==pas){
            account.close();
           return 1;
        }
    }
    account.close();
    return  status;
}

string Admin::search_low(){//0代表没有找到
    fstream account;
    account.open("data.acc",ios_base::in);
    if(!account) {
        account.close();
        return "\0";
    }
    string acc_,pas_,dat_,tem;
    while(!account.eof()){
        getline(account,tem,'=');
        if(tem=="account")getline(account,acc_,';');
        else if (tem=="password") {
            getline(account,pas_,';');
            Decode(pas_);
        }
        else getline(account,dat_,';');
        if(acc_==acc&&pas_==pas){
            account.close();
           return dat_;
        }
    }
    account.close();
    return  "\0";
}
