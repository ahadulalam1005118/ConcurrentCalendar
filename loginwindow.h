#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
//#include "client.h"
#include <iostream>
#include <string>
#include<mainwindow.h>
using namespace std;

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    client m_client;
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::LoginWindow *ui;
    static string command;
    MainWindow *mw;

    //client m_client;
};

#endif // LOGINWINDOW_H
