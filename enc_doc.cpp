#include"enc_doc.h"

string& Encrypt(string &passw){
    char *password = nullptr;
    password=new char[passw.length()];
    strcpy(password,passw.c_str());
    for(unsigned int i=0;i<strlen(password);i=i+3)
    {
        password[i]+=i;
    }
    for(unsigned int i=1;i<strlen(password);i=i+3)
    {
        password[i]-=i;
    }
    for(unsigned int i=2;i<strlen(password);i=i+3)
    {
        password[i]=password[i]*2;
    }
    passw=password;
    return passw;
}


string& Decode(string &passw){
    char *password = nullptr;
    password=new char[passw.length()];
    strcpy(password,passw.c_str());

    for(unsigned int i=2;i<strlen(password);i=i+3)
    {
        password[i]=password[i]/2;
    }

    for(unsigned int i=1;i<strlen(password);i=i+3)
    {
        password[i]+=i;
    }

    for(unsigned int i=0;i<strlen(password);i=i+3)
    {
        password[i]-=i;
    }
    passw=password;
    return passw;
}
