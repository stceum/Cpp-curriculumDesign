 #include "delay.h"
#include<QApplication>

void sleep(int msec){
    //使用currentTime返回当前时间，并且用当前时间加上需要延时的时间
    QTime reachTime=QTime::currentTime().addMSecs(msec);

    while (QTime::currentTime()<reachTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
};
