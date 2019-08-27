#ifndef STU_H
#define STU_H
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
class MainWindow;

typedef struct course_{
    string cour;
    float grade;
    course_();
}course;

typedef struct for_sort for_s;
for_s * get_data(string filNm,int num);
class Stu{

    string name;
    bool sex;
    string id;
    string major;
    int num;
    course *cour;
    float t_grade;

public:
    friend class MainWindow;
    friend bool operator==(Stu &a,Stu &b);
    Stu();
    Stu(const Stu &tar);//copy construct function 
    
    /*if the index equals to -1,then put the target at the eof
	else change the data at the index to the target*/
    friend bool wtFile(string filename,Stu &tar,long long index);//write/edit to file>>>0 faile 1 success
    friend bool clnLit(string filNm);//clean the litter data
    friend Stu rfFile(string filename,long long index);//read from file>>>return the Stu
    friend bool dfFile(string filename,long long index);
    //friend Stu _test();//temp
    friend bool srch(string filename,Stu &tar);
    friend for_s * get_data(string filNm,int num);
};

bool wtFile(string filename,Stu &tar,long long index=-1);
bool clnLit(string filNm);
Stu rfFile(string filename,long long index);
bool dfFile(string filename,long long index);
//Stu _test();
bool srch(string filename,Stu &tar);
bool s_jug(string &a,string &b);

#endif
