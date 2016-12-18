#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    // example to excute query
    /*
    QSqlQuery l;
    l.exec("select * from Employee");
    */

    return a.exec();
}
