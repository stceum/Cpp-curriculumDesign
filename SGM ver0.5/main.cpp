#include "widget.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget *login=new Widget;
    MainWindow *editor=nullptr;
    editor=new MainWindow;
    login->show();

    QObject::connect(login,SIGNAL(loginquit()),editor,SLOT(editorshow()));
    QObject::connect(login,SIGNAL(visitorcomes()),editor,SLOT(readershow()));
    QObject::connect(editor,SIGNAL(editorquit()),login,SLOT(loginshow()));
    QObject::connect(login,SIGNAL(send_filename(string)),editor,SLOT(read_file(string)));

    return a.exec();
}
