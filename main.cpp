#include "mainwindow.h"
#include "loginwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //LoginWindow lw;
    //lw.show();

    MainWindow w;
    LoginWindow l;
    //connect(&l, SIGNAL(loggedIn), &w, SLOT(show());
    l.show();
    //MainWindow w;
    //w.show();

    return a.exec();
}
