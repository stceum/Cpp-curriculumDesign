#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <iostream>
#include <sstream>
#include "Stu.h"
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void prog(int value);
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();




private slots:

    void editorshow();
    void readershow();
    void ini();

    void list_1_refresh();
    void list_1_selected_changed();
    void clear(int mode=1);
    void clearmode();

    void id_change();
    void name_change();
    void major_change();
    void sex_change();

    void course_n_change();
    void course_name_change();
    void grade_change();
    void list_2_refresh();
    void list_2_selected_changed();

    void read_file(string filename);
    void add_new();
    void change_old();
    void del_sel();
    void defrag();

    void list_1_refresh_srch();
    void list_1_selected_changed_srch();
    void srch_mode();
signals:
    void editorquit();

private:
    Ui::MainWindow *ui;
    string fiN;//filename that prepare to open
    bool anEdi;
    Stu temp;
    long long point;
    int mode;
};


#endif // MAINWINDOW_H
