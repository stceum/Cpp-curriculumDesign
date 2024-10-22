#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "admin.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    using namespace std;
    ui->setupUi(this);
}


void MainWindow::backup(){
    fstream ind((fiN+".ind").c_str(),ios_base::in);
    long long point;
    while(!ind.eof()){
        ind>>point;
        Stu temp;
        temp=rfFile(fiN,point);
        wtFile((fiN+".bac"),temp);
    }
    ind.close();
    list_1_refresh();
    ui->statusBar->setStyleSheet("color:green;");
    ui->statusBar->showMessage(tr("√√√√√备份成功√√√√√"),2000);
}

void MainWindow::recover(){
    remove(fiN.c_str());
    remove((fiN+".ind").c_str());
    fstream ind((fiN+".bac"+".ind").c_str(),ios_base::in);
    long long point;
    while(!ind.eof()){
        ind>>point;
        Stu temp;
        temp=rfFile(fiN+".bac",point);
        wtFile(fiN,temp);
    }
    ind.close();
    list_1_refresh();
    ui->statusBar->setStyleSheet("color:green;");
    ui->statusBar->showMessage(tr("√√√√√恢复成功√√√√√"),2000);
}

void MainWindow::editorshow(){

    delete ui;
    ui=new Ui::MainWindow;
    ui->setupUi(this);
    connect(ui->exit,SIGNAL(clicked()),this,SIGNAL(editorquit()));
    connect(ui->action_8,SIGNAL(triggered()),this,SLOT(defrag()));
    connect(ui->search,SIGNAL(clicked()),this,SLOT(srch_mode()));
    connect(ui->sort,SIGNAL(clicked()),this,SLOT(sort_mode()));
    connect(ui->action_3,SIGNAL(triggered()),this,SIGNAL(editorquit()));
    connect(ui->action_6,SIGNAL(triggered()),this,SLOT(backup()));
    connect(ui->action_7,SIGNAL(triggered()),this,SLOT(recover()));
    anEdi=true;
    mode=0;
    //启用编辑
    connect(ui->course,SIGNAL(valueChanged(int)),this,SLOT(course_n_change()));
    connect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(course_name_change()));
    connect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    connect(ui->grade,SIGNAL(editingFinished()),this,SLOT(grade_change()));
    connect(ui->grade,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    connect(ui->listWidget_2,SIGNAL(currentRowChanged(int)),this,SLOT(list_2_selected_changed()));
    connect(ui->add,SIGNAL(clicked()),this,SLOT(add_new()));

    connect(ui->name,SIGNAL(editingFinished()),this,SLOT(name_change()));
    connect(ui->id,SIGNAL(editingFinished()),this,SLOT(id_change()));
    connect(ui->major,SIGNAL(editingFinished()),this,SLOT(major_change()));
    connect(ui->sex,SIGNAL(currentIndexChanged(int)),this,SLOT(sex_change()));

    connect(ui->listWidget_1,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(list_1_selected_changed()));
    connect(ui->clear,SIGNAL(clicked()),this,SLOT(clearmode()));
    connect(ui->subm,SIGNAL(clicked()),this,SLOT(change_old()));
    connect(ui->del,SIGNAL(clicked()),this,SLOT(del_sel()));
    this->show();
     ui->statusBar->showMessage(tr("欢迎来到管理员界面！"),2000);
     ini();
     clear(0);
}

void MainWindow::readershow(){
    delete ui;
    ui=new Ui::MainWindow;
    ui->setupUi(this);
    connect(ui->exit,SIGNAL(clicked()),this,SIGNAL(editorquit()));
    connect(ui->action_8,SIGNAL(triggered()),this,SLOT(defrag()));
    connect(ui->search,SIGNAL(clicked()),this,SLOT(srch_mode()));
    connect(ui->sort,SIGNAL(clicked()),this,SLOT(sort_mode()));
    anEdi=false;
    mode=0;
    //禁用编辑
    connect(ui->listWidget_2,SIGNAL(currentRowChanged(int)),this,SLOT(list_2_selected_changed()));
    ui->t_grade->setEnabled(false);
    ui->add->setEnabled(false);
    ui->del->setEnabled(false);
    ui->menu->setEnabled(false);
    ui->cour_name->setEnabled(false);
    ui->grade->setEnabled(false);
    ui->label->setEnabled(false);
    ui->course->setEnabled(false);
    ui->menu_2->setEnabled(false);
    ui->subm->setEnabled(false);
    ui->clear->setEnabled(false);
    connect(ui->listWidget_1,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(list_1_selected_changed()));
    this->show();
    ui->statusBar->showMessage(tr("欢迎来到访问者界面！"),2000);
    ini();
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::ini(){
    fstream file(fiN.c_str(),ios_base::out|ios_base::in);
    fstream index((fiN+".ind").c_str(),ios_base::out|ios_base::in);
    num_of_stu=0;
    int i=0;

    while(!index.eof()){

           long long point=0;
           if(index>>point)
                file.seekp(point);
           else {
               break;
           }
           //读取完一个学生的信息
           getline(file,temp.name,';');

           stringstream stri;
           string str;

           getline(file,str,';');
           stri<<str;
           stri>>temp.sex;

           getline(file,temp.id,';');

           getline(file,temp.major,';');

           stri.clear();
           if(getline(file,str,';'));
           else {
               break;
           }
           stri<<str;
           stri>>temp.num;

           if(temp.num!=0)
           {
               temp.cour=new course[temp.num];
               for (int i=0;i<temp.num;i++) {

                   getline(file,temp.cour[i].cour,';');
                   getline(file,str,';');
                   stri<<str;
                   stri>>temp.cour[i].grade;
               }
           }

           QListWidgetItem *item = new QListWidgetItem;

           std::stringstream num_;
           string _sex;

           if(temp.sex==0)
               _sex="男";
           else{
               _sex="女";
           }


           num_<<temp.num;
           string _num_;
           num_>>_num_;

           string list= temp.name +" : " +temp.id +"\t"+_sex
                   +"\t"+temp.major+"\t"+"课程数:"+_num_;
           item->setText(QString::fromStdString(list));

           if(i%2){
               item->setBackground(QColor(255,255,255));
           }
           else {
               item->setBackground(QColor(220,220,220));
           }
           i++;
           ui->listWidget_1->addItem(item);
           num_of_stu++;
       }
       file.close();
       index.close();
}

void MainWindow::list_1_refresh(){
    int currentRow=ui->listWidget_1->currentRow();
    if(currentRow>ui->listWidget_1->count()){
        currentRow=-1;
    }
    disconnect(ui->course,SIGNAL(valueChanged(int)),this,SLOT(course_n_change()));
    disconnect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(course_name_change()));
    disconnect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    disconnect(ui->grade,SIGNAL(editingFinished()),this,SLOT(grade_change()));
    disconnect(ui->grade,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    disconnect(ui->listWidget_2,SIGNAL(currentRowChanged(int)),this,SLOT(list_2_selected_changed()));
    disconnect(ui->add,SIGNAL(clicked()),this,SLOT(add_new()));
    disconnect(ui->name,SIGNAL(editingFinished()),this,SLOT(name_change()));
    disconnect(ui->id,SIGNAL(editingFinished()),this,SLOT(id_change()));
    disconnect(ui->major,SIGNAL(editingFinished()),this,SLOT(major_change()));
    disconnect(ui->sex,SIGNAL(currentIndexChanged(int)),this,SLOT(sex_change()));

    int counter = ui->listWidget_1->count();
    QListWidgetItem *item;
    for(int index = 0;index <counter;index++)
    {
        item = ui->listWidget_1->takeItem(0);
        if(item!=nullptr)
        delete item;

    }
    ini();
    if(currentRow!=-1)
        ui->listWidget_1->setCurrentRow(currentRow);

    connect(ui->course,SIGNAL(valueChanged(int)),this,SLOT(course_n_change()));
    connect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(course_name_change()));
    connect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    connect(ui->grade,SIGNAL(editingFinished()),this,SLOT(grade_change()));
    connect(ui->grade,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    connect(ui->listWidget_2,SIGNAL(currentRowChanged(int)),this,SLOT(list_2_selected_changed()));
    connect(ui->add,SIGNAL(clicked()),this,SLOT(add_new()));

    connect(ui->name,SIGNAL(editingFinished()),this,SLOT(name_change()));
    connect(ui->id,SIGNAL(editingFinished()),this,SLOT(id_change()));
    connect(ui->major,SIGNAL(editingFinished()),this,SLOT(major_change()));
    connect(ui->sex,SIGNAL(currentIndexChanged(int)),this,SLOT(sex_change()));
}


void MainWindow::list_1_selected_changed(){
    disconnect(ui->course,SIGNAL(valueChanged(int)),this,SLOT(course_n_change()));
    disconnect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(course_name_change()));
    disconnect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    disconnect(ui->grade,SIGNAL(editingFinished()),this,SLOT(grade_change()));
    disconnect(ui->grade,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    disconnect(ui->listWidget_2,SIGNAL(currentRowChanged(int)),this,SLOT(list_2_selected_changed()));
    disconnect(ui->add,SIGNAL(clicked()),this,SLOT(add_new()));

    disconnect(ui->name,SIGNAL(editingFinished()),this,SLOT(name_change()));
    disconnect(ui->id,SIGNAL(editingFinished()),this,SLOT(id_change()));
    disconnect(ui->major,SIGNAL(editingFinished()),this,SLOT(major_change()));
    disconnect(ui->sex,SIGNAL(currentIndexChanged(int)),this,SLOT(sex_change()));

    fstream ind((fiN+".ind").c_str(),ios_base::in);
    int cuR=ui->listWidget_1->currentRow();
    ind>>point;
    for (int i=0;i<cuR;i++) {
           ind>>point;
    }
    ind.close();
    clear(0);
    temp=rfFile(fiN,point);
    ui->name->setText(QString::fromStdString(temp.name));
    ui->id->setText(QString::fromStdString(temp.id));
    ui->major->setText(QString::fromStdString(temp.major));
    ui->sex->setCurrentIndex(temp.sex);
    ui->course->setValue(temp.num);
    stringstream stri;
    stri<<temp.t_grade;
    string strr;
    stri>>strr;
    ui->t_grade->setText(QString::fromStdString(strr));
    list_2_refresh();

    connect(ui->course,SIGNAL(valueChanged(int)),this,SLOT(course_n_change()));
    connect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(course_name_change()));
    connect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    connect(ui->grade,SIGNAL(editingFinished()),this,SLOT(grade_change()));
    connect(ui->grade,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    connect(ui->listWidget_2,SIGNAL(currentRowChanged(int)),this,SLOT(list_2_selected_changed()));
    connect(ui->add,SIGNAL(clicked()),this,SLOT(add_new()));

    connect(ui->name,SIGNAL(editingFinished()),this,SLOT(name_change()));
    connect(ui->id,SIGNAL(editingFinished()),this,SLOT(id_change()));
    connect(ui->major,SIGNAL(editingFinished()),this,SLOT(major_change()));
    connect(ui->sex,SIGNAL(currentIndexChanged(int)),this,SLOT(sex_change()));
}

void MainWindow::clearmode(){
    ui->course->setEnabled(true);
    clear(1);
}

void MainWindow::clear(int mode){//clear the left information before
    if(mode==1){
        disconnect(ui->listWidget_1,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(list_1_selected_changed_srch()));
        connect(ui->listWidget_1,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(list_1_selected_changed()));
        list_1_refresh();
    }
    if(mode==2){
        disconnect(ui->listWidget_1,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(list_1_selected_changed_sort()));
        connect(ui->listWidget_1,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(list_1_selected_changed()));
        list_1_refresh();
    }

    ui->name->setText("");
    ui->sex->setCurrentIndex(0);
    ui->id->setText("");
    ui->course->setValue(0);
    ui->major->setText("");
    ui->t_grade->setText("");
    ui->label_3->setText("");
    ui->cour_name->setText("");
    ui->grade->setText("");
    ui->cour_name->setEnabled(false);
    ui->grade->setEnabled(false);
    Stu nul;//clear the current temp
    temp=nul;
    list_2_refresh();
}

void MainWindow::id_change(){
    temp.id=(ui->id->text()).toStdString();
}

void MainWindow::name_change(){
    temp.name=(ui->name->text()).toStdString();
}

void MainWindow::major_change(){
    temp.major=(ui->major->text()).toStdString();
}

void MainWindow::sex_change(){
    temp.sex=ui->sex->currentIndex();
}

void MainWindow::course_n_change(){//修改课程数目
    disconnect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(course_name_change()));
    disconnect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));

    disconnect(ui->grade,SIGNAL(editingFinished()),this,SLOT(grade_change()));
    disconnect(ui->grade,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));

    disconnect(ui->listWidget_2,SIGNAL(currentRowChanged(int)),this,SLOT(list_2_selected_changed()));
    ui->cour_name->setEnabled(false);
    ui->grade->setEnabled(false);

    temp.num=ui->course->value();
    if(temp.num!=0)
        temp.cour=new course[temp.num];
    list_2_refresh();

    connect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(course_name_change()));
    connect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));

    connect(ui->grade,SIGNAL(editingFinished()),this,SLOT(grade_change()));
    connect(ui->grade,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));

    connect(ui->listWidget_2,SIGNAL(currentRowChanged(int)),this,SLOT(list_2_selected_changed()));
}

void MainWindow::course_name_change(){//修改课程信息与课程文本框相连

    disconnect(ui->listWidget_2,SIGNAL(currentRowChanged(int)),this,SLOT(list_2_selected_changed()));

    int i=ui->listWidget_2->currentRow();
    if(i!=-1)
        temp.cour[i].cour=ui->cour_name->text().toStdString();
}

void MainWindow::grade_change(){//修改成绩信息与成绩文本框相连

    disconnect(ui->listWidget_2,SIGNAL(currentRowChanged(int)),this,SLOT(list_2_selected_changed()));

    int i=ui->listWidget_2->currentRow();
    std::stringstream stream;
    stream<<ui->grade->text().toStdString();
    if(i!=-1)
        stream>>temp.cour[i].grade;

    int total=0;
    if(temp.num!=0)
    {
        for (int i=0;i<temp.num;i++) {
            total+=temp.cour[i].grade;
        }
    }
    else {
        return;
    }

    stringstream _t_grade;
    if(temp.num!=0)
    _t_grade<<(total/temp.num);
    else {
        _t_grade<<0;
    }
    string t_grade;
    _t_grade>>t_grade;
    ui->t_grade->setText(QString::fromStdString(t_grade));
}

void MainWindow::list_2_refresh(){//更新列表

    //获取当前的选项
    int currentRow=ui->listWidget_2->currentRow();

    //清空
    int counter = ui->listWidget_2->count();

    QListWidgetItem *item;
    for(int index = 0;index <counter;index++)
    {

        item = ui->listWidget_2->takeItem(0);
        if(item!=nullptr)
        delete item;

    }

    //重写
    for (int i=0;i<temp.num;i++) {
        item = new QListWidgetItem;

        std::stringstream num_,grade_;

        grade_<<temp.cour[i].grade;
        string _grade_;
        grade_>>_grade_;

        num_<<(i+1);
        string _num_;
        num_>>_num_;
        string list;
        if(temp.cour[i].cour.length()<8)
        {
            list= _num_ + ":" + "课程:" + temp.cour[i].cour +
                    "\t\t成绩:"+_grade_;
        }
        else {
            list= _num_ + ":" + "课程:" + temp.cour[i].cour +
                    "\t成绩:"+_grade_;
        }
        item->setText(QString::fromStdString(list));
        if(i%2){
            item->setBackground(QColor(255,240,245));
        }
        else {
            item->setBackground(QColor(255,255,244));
        }
        ui->listWidget_2->addItem(item);
    }

    if(currentRow!=-1)
    ui->listWidget_2->setCurrentRow(currentRow);


    connect(ui->listWidget_2,SIGNAL(currentRowChanged(int)),this,SLOT(list_2_selected_changed()));
}

void MainWindow::list_2_selected_changed(){
    if(anEdi)
    {
        ui->cour_name->setEnabled(1);
        ui->grade->setEnabled(1);
    }
    else {
        ui->cour_name->setEnabled(0);
        ui->grade->setEnabled(0);
    }

    std::stringstream int_str,flo_str;
    string a;

    int currentRow=ui->listWidget_2->currentRow();
    int_str<<currentRow+1;
    int_str>>a;
    ui->label_3->setText(QString::fromStdString(a));

    flo_str<<temp.cour[currentRow].grade;
    flo_str>>a;
    ui->cour_name->setText(QString::fromStdString(temp.cour[currentRow].cour));
    ui->grade->setText(QString::fromStdString(a));
}



void MainWindow::read_file(string filename){
    fiN=filename;
}

void MainWindow::add_new(){
    if((temp.id!="")&&(temp.name!="")&&(temp.major!="")){
        wtFile(fiN,temp);
        //clear the data that have been writen to the file
        clear(0);
        ui->statusBar->setStyleSheet("color:green;");
        ui->statusBar->showMessage(tr("√√√√√添加成功√√√√√"),2000);
        list_1_refresh();
    }
    else {
        ui->statusBar->setStyleSheet("color:red;");
        ui->statusBar->showMessage(tr("xxxxx非法添加xxxxx"),2000);
    }
    clear(1);
}

void MainWindow::change_old(){
    if(ui->listWidget_1->currentRow()!=-1){
        wtFile(fiN,temp,point);
        ui->statusBar->setStyleSheet("color:green;");
        ui->statusBar->showMessage(tr("√√√√√修改成功√√√√√"),2000);
        list_1_refresh();
    }
    else {
        ui->statusBar->setStyleSheet("color:red;");
        ui->statusBar->showMessage(tr("xxxxx非法提交xxxxx"),2000);
    }
    clear(1);
}

void MainWindow::del_sel(){
    dfFile(fiN,point);
    ui->statusBar->setStyleSheet("color:green;");
    ui->statusBar->showMessage(tr("√√√√√删除成功√√√√√"),2000);
    list_1_refresh();
    clear(1);
}

void MainWindow::defrag(){//delete the litter in the file
    clnLit(fiN);
    ui->statusBar->setStyleSheet("color:green;");
    ui->statusBar->showMessage(tr("√√√√√碎片整理成功√√√√√"),2000);
    clear(1);
}

void MainWindow::list_1_refresh_srch(){
    int currentRow=ui->listWidget_1->currentRow();
    if(currentRow>ui->listWidget_1->count()){
        currentRow=-1;
    }
    disconnect(ui->course,SIGNAL(valueChanged(int)),this,SLOT(course_n_change()));
    disconnect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(course_name_change()));
    disconnect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    disconnect(ui->grade,SIGNAL(editingFinished()),this,SLOT(grade_change()));
    disconnect(ui->grade,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    disconnect(ui->listWidget_2,SIGNAL(currentRowChanged(int)),this,SLOT(list_2_selected_changed()));
    disconnect(ui->add,SIGNAL(clicked()),this,SLOT(add_new()));

    disconnect(ui->name,SIGNAL(editingFinished()),this,SLOT(name_change()));
    disconnect(ui->id,SIGNAL(editingFinished()),this,SLOT(id_change()));
    disconnect(ui->major,SIGNAL(editingFinished()),this,SLOT(major_change()));
    disconnect(ui->sex,SIGNAL(currentIndexChanged(int)),this,SLOT(sex_change()));

    int counter = ui->listWidget_1->count();
    QListWidgetItem *item;
    for(int index = 0;index <counter;index++)
    {

        item = ui->listWidget_1->takeItem(0);
        if(item!=nullptr)
        delete item;

    }
    //read items from the file
    fstream file(fiN.c_str(),ios_base::out|ios_base::in);
    fstream index("res",ios_base::out|ios_base::in);
    int i=0;

    while(!index.eof()){

           long long point=0;
           if(index>>point)
                file.seekp(point);
           else {
               break;
           }
           //读取完一个学生的信息
           getline(file,temp.name,';');

           stringstream stri;
           string str;

           getline(file,str,';');
           stri<<str;
           stri>>temp.sex;

           getline(file,temp.id,';');

           getline(file,temp.major,';');

           stri.clear();
           if(getline(file,str,';'));
           else {
               break;
           }
           stri<<str;
           stri>>temp.num;

           if(temp.num!=0)
           {
               temp.cour=new course[temp.num];
               for (int i=0;i<temp.num;i++) {

                   getline(file,temp.cour[i].cour,';');
                   getline(file,str,';');
                   stri<<str;
                   stri>>temp.cour[i].grade;
               }
           }

           QListWidgetItem *item = new QListWidgetItem;

           std::stringstream num_;
           string _sex;

           if(temp.sex==0)
               _sex="男";
           else{
               _sex="女";
           }


           num_<<temp.num;
           string _num_;
           num_>>_num_;
           string list= temp.name +":" +temp.id +"\t"+_sex
                   +"\t"+temp.major+"\t"+"课程数:"+_num_;
           item->setText(QString::fromStdString(list));

           if(i%2){
               item->setBackground(QColor(255,255,255));
           }
           else {
               item->setBackground(QColor(220,220,220));
           }
           i++;
           ui->listWidget_1->addItem(item);
       }
       file.close();
       index.close();
    if(currentRow!=-1)
        ui->listWidget_1->setCurrentRow(currentRow);

    connect(ui->course,SIGNAL(valueChanged(int)),this,SLOT(course_n_change()));
    connect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(course_name_change()));
    connect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    connect(ui->grade,SIGNAL(editingFinished()),this,SLOT(grade_change()));
    connect(ui->grade,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    connect(ui->listWidget_2,SIGNAL(currentRowChanged(int)),this,SLOT(list_2_selected_changed()));
    connect(ui->add,SIGNAL(clicked()),this,SLOT(add_new()));

    connect(ui->name,SIGNAL(editingFinished()),this,SLOT(name_change()));
    connect(ui->id,SIGNAL(editingFinished()),this,SLOT(id_change()));
    connect(ui->major,SIGNAL(editingFinished()),this,SLOT(major_change()));
    connect(ui->sex,SIGNAL(currentIndexChanged(int)),this,SLOT(sex_change()));
}

void MainWindow::list_1_selected_changed_srch(){
    disconnect(ui->course,SIGNAL(valueChanged(int)),this,SLOT(course_n_change()));
    disconnect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(course_name_change()));
    disconnect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    disconnect(ui->grade,SIGNAL(editingFinished()),this,SLOT(grade_change()));
    disconnect(ui->grade,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    disconnect(ui->listWidget_2,SIGNAL(currentRowChanged(int)),this,SLOT(list_2_selected_changed()));
    disconnect(ui->add,SIGNAL(clicked()),this,SLOT(add_new()));

    disconnect(ui->name,SIGNAL(editingFinished()),this,SLOT(name_change()));
    disconnect(ui->id,SIGNAL(editingFinished()),this,SLOT(id_change()));
    disconnect(ui->major,SIGNAL(editingFinished()),this,SLOT(major_change()));
    disconnect(ui->sex,SIGNAL(currentIndexChanged(int)),this,SLOT(sex_change()));

    fstream ind("res",ios_base::in);
    int cuR=ui->listWidget_1->currentRow();
    ind>>point;
    for (int i=0;i<cuR;i++) {
           ind>>point;
    }
    ind.close();
    clear(0);
    temp=rfFile(fiN,point);
    ui->name->setText(QString::fromStdString(temp.name));
    ui->id->setText(QString::fromStdString(temp.id));
    ui->major->setText(QString::fromStdString(temp.major));
    ui->sex->setCurrentIndex(temp.sex);
    ui->course->setValue(temp.num);
    stringstream stri;
    stri<<temp.t_grade;
    string strr;
    stri>>strr;
    ui->t_grade->setText(QString::fromStdString(strr));
    list_2_refresh();

    connect(ui->course,SIGNAL(valueChanged(int)),this,SLOT(course_n_change()));
    connect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(course_name_change()));
    connect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    connect(ui->grade,SIGNAL(editingFinished()),this,SLOT(grade_change()));
    connect(ui->grade,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    connect(ui->listWidget_2,SIGNAL(currentRowChanged(int)),this,SLOT(list_2_selected_changed()));
    connect(ui->add,SIGNAL(clicked()),this,SLOT(add_new()));

    connect(ui->name,SIGNAL(editingFinished()),this,SLOT(name_change()));
    connect(ui->id,SIGNAL(editingFinished()),this,SLOT(id_change()));
    connect(ui->major,SIGNAL(editingFinished()),this,SLOT(major_change()));
    connect(ui->sex,SIGNAL(currentIndexChanged(int)),this,SLOT(sex_change()));
}

void MainWindow::srch_mode(){
    if(mode==2)
        clear(2);
    //change the show mode into search mode
    disconnect(ui->listWidget_1,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(list_1_selected_changed()));
    connect(ui->listWidget_1,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(list_1_selected_changed_srch()));
    ui->course->setEnabled(false);
    temp.num=0;
    temp.cour=nullptr;
    temp.name=ui->name->text().toStdString();
    temp.sex=ui->sex->currentIndex();
    temp.id=ui->id->text().toStdString();
    temp.major=ui->major->text().toStdString();
    srch(fiN,temp);
    list_1_refresh_srch();
}

void MainWindow::list_1_refresh_sort(){
    int currentRow=ui->listWidget_1->currentRow();
    if(currentRow>ui->listWidget_1->count()){
        currentRow=-1;
    }
    disconnect(ui->course,SIGNAL(valueChanged(int)),this,SLOT(course_n_change()));
    disconnect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(course_name_change()));
    disconnect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    disconnect(ui->grade,SIGNAL(editingFinished()),this,SLOT(grade_change()));
    disconnect(ui->grade,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    disconnect(ui->listWidget_2,SIGNAL(currentRowChanged(int)),this,SLOT(list_2_selected_changed()));
    disconnect(ui->add,SIGNAL(clicked()),this,SLOT(add_new()));

    disconnect(ui->name,SIGNAL(editingFinished()),this,SLOT(name_change()));
    disconnect(ui->id,SIGNAL(editingFinished()),this,SLOT(id_change()));
    disconnect(ui->major,SIGNAL(editingFinished()),this,SLOT(major_change()));
    disconnect(ui->sex,SIGNAL(currentIndexChanged(int)),this,SLOT(sex_change()));

    int counter = ui->listWidget_1->count();
    QListWidgetItem *item;
    for(int index = 0;index <counter;index++)
    {

        item = ui->listWidget_1->takeItem(0);
        if(item!=nullptr)
        delete item;

    }
    //read items from the file
    fstream file(fiN.c_str(),ios_base::out|ios_base::in);
    fstream index("sort",ios_base::out|ios_base::in);
    int i=0;
    while(!index.eof()){

           long long point=0;
           if(index>>point)
                file.seekp(point);
           else {
               break;
           }
           //读取完一个学生的信息
           getline(file,temp.name,';');

           stringstream stri;
           string str;

           getline(file,str,';');
           stri<<str;
           stri>>temp.sex;

           getline(file,temp.id,';');

           getline(file,temp.major,';');

           stri.clear();
           if(getline(file,str,';'));
           else {
               break;
           }
           stri<<str;
           stri>>temp.num;

           if(temp.num!=0)
           {
               temp.cour=new course[temp.num];
               for (int i=0;i<temp.num;i++) {

                   getline(file,temp.cour[i].cour,';');
                   getline(file,str,';');
                   stri<<str;
                   stri>>temp.cour[i].grade;
               }
           }

           QListWidgetItem *item = new QListWidgetItem;

           std::stringstream num_;
           string _sex;

           if(temp.sex==0)
               _sex="男";
           else{
               _sex="女";
           }


           num_<<temp.num;
           string _num_;
           num_>>_num_;
           string list= temp.name +":" +temp.id +"\t"+_sex
                   +"\t"+temp.major+"\t"+"课程数:"+_num_;
           item->setText(QString::fromStdString(list));

           if(i%2){
               item->setBackground(QColor(255,255,255));
           }
           else {
               item->setBackground(QColor(220,220,220));
           }
           i++;
           ui->listWidget_1->addItem(item);
       }
       file.close();
       index.close();
    if(currentRow!=-1)
        ui->listWidget_1->setCurrentRow(currentRow);

    connect(ui->course,SIGNAL(valueChanged(int)),this,SLOT(course_n_change()));
    connect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(course_name_change()));
    connect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    connect(ui->grade,SIGNAL(editingFinished()),this,SLOT(grade_change()));
    connect(ui->grade,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    connect(ui->listWidget_2,SIGNAL(currentRowChanged(int)),this,SLOT(list_2_selected_changed()));
    connect(ui->add,SIGNAL(clicked()),this,SLOT(add_new()));

    connect(ui->name,SIGNAL(editingFinished()),this,SLOT(name_change()));
    connect(ui->id,SIGNAL(editingFinished()),this,SLOT(id_change()));
    connect(ui->major,SIGNAL(editingFinished()),this,SLOT(major_change()));
    connect(ui->sex,SIGNAL(currentIndexChanged(int)),this,SLOT(sex_change()));
}

void MainWindow::list_1_selected_changed_sort(){
    disconnect(ui->course,SIGNAL(valueChanged(int)),this,SLOT(course_n_change()));
    disconnect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(course_name_change()));
    disconnect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    disconnect(ui->grade,SIGNAL(editingFinished()),this,SLOT(grade_change()));
    disconnect(ui->grade,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    disconnect(ui->listWidget_2,SIGNAL(currentRowChanged(int)),this,SLOT(list_2_selected_changed()));
    disconnect(ui->add,SIGNAL(clicked()),this,SLOT(add_new()));

    disconnect(ui->name,SIGNAL(editingFinished()),this,SLOT(name_change()));
    disconnect(ui->id,SIGNAL(editingFinished()),this,SLOT(id_change()));
    disconnect(ui->major,SIGNAL(editingFinished()),this,SLOT(major_change()));
    disconnect(ui->sex,SIGNAL(currentIndexChanged(int)),this,SLOT(sex_change()));

    fstream ind("sort",ios_base::in);
    int cuR=ui->listWidget_1->currentRow();
    ind>>point;
    for (int i=0;i<cuR;i++) {
           ind>>point;
    }
    ind.close();
    clear(0);
    temp=rfFile(fiN,point);
    ui->name->setText(QString::fromStdString(temp.name));
    ui->id->setText(QString::fromStdString(temp.id));
    ui->major->setText(QString::fromStdString(temp.major));
    ui->sex->setCurrentIndex(temp.sex);
    ui->course->setValue(temp.num);
    stringstream stri;
    stri<<temp.t_grade;
    string strr;
    stri>>strr;
    ui->t_grade->setText(QString::fromStdString(strr));
    list_2_refresh();

    connect(ui->course,SIGNAL(valueChanged(int)),this,SLOT(course_n_change()));
    connect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(course_name_change()));
    connect(ui->cour_name,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    connect(ui->grade,SIGNAL(editingFinished()),this,SLOT(grade_change()));
    connect(ui->grade,SIGNAL(editingFinished()),this,SLOT(list_2_refresh()));
    connect(ui->listWidget_2,SIGNAL(currentRowChanged(int)),this,SLOT(list_2_selected_changed()));
    connect(ui->add,SIGNAL(clicked()),this,SLOT(add_new()));

    connect(ui->name,SIGNAL(editingFinished()),this,SLOT(name_change()));
    connect(ui->id,SIGNAL(editingFinished()),this,SLOT(id_change()));
    connect(ui->major,SIGNAL(editingFinished()),this,SLOT(major_change()));
    connect(ui->sex,SIGNAL(currentIndexChanged(int)),this,SLOT(sex_change()));
}

void MainWindow::sort_mode(){
    if(mode==1)
        clear(1);
    int status=ui->ComboBox->currentIndex();
     /*when the row that was selected was 0,what wee need to do is to clear all of the infor*/
    if(status==0){
        //clear
        clear(2);
    }
    else if (status==1) {
        //produce the "sort" file,then read the file
        mode=2;
        wrtFil_sort(QwkSort(get_data(fiN,num_of_stu),0,num_of_stu-1),num_of_stu);
        disconnect(ui->listWidget_1,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(list_1_selected_changed()));
        connect(ui->listWidget_1,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(list_1_selected_changed_sort()));
        list_1_refresh_sort();
    }
}
