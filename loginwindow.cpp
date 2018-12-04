#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <string>
#include "mainwindow.h"
#include <QApplication>
#include<unistd.h>
using namespace std;
string LoginWindow::command = "";
LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    //vector<friends_info> client::friends_list = {};
    //vector<connected_friends> client::friends_sockfd = {};
    std::string _configuration_file = "/home/ahad/EventCalendar/configurations";
   // mw = new MainWindow(m_client,this);
    m_client.begin(_configuration_file);
    m_client.run();
    ui->setupUi(this);
    ui->label->hide();
    ui->label_2->hide();
    ui->textEdit->hide();
    ui->textEdit_2->hide();
    ui->pushButton_3->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->textEdit_3->hide();
    ui->textEdit_4->hide();
    ui->pushButton_4->hide();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_clicked() //login button
{
    ui->label_3->hide();
    ui->label_4->hide();
    ui->textEdit_3->hide();
    ui->textEdit_4->hide();
    ui->pushButton_4->hide();
    ui->label->show();
    ui->label_2->show();
    ui->textEdit->show();
    ui->textEdit_2->show();
    ui->pushButton_3->show();
    command.clear();
    command.append("l");

}

void LoginWindow::on_pushButton_2_clicked() //registration button
{
    ui->label->hide();
    ui->label_2->hide();
    ui->textEdit->hide();
    ui->textEdit_2->hide();
    ui->pushButton_3->hide();
    ui->label_3->show();
    ui->label_4->show();
    ui->textEdit_3->show();
    ui->textEdit_4->show();
    ui->pushButton_4->show();
    command.clear();
    command.append("r");
}

void LoginWindow::on_pushButton_3_clicked() //submit button
{
    command.append("#");
    command.append(ui->textEdit_2->toPlainText().toStdString()); //username
    command.append("#");
    command.append(ui->textEdit->toPlainText().toStdString()); //password
    m_client.write_to_sockfd(command);
    command.clear();
    sleep(2);
    ui->pushButton_3->disconnect();
    if(m_client.login_status == true) {
        //MainWindow mw;
        mw = new MainWindow(m_client,this);
        hide();
        mw->show();
        //mw->m_client = m_client;
        //string result = mw->on_submitButton_clicked();
        //m_client.write_to_sockfd(result);
        //this->close();
    }

    //connect(&l, SIGNAL(loggedIn), &w, SLOT(show());

}

void LoginWindow::on_pushButton_4_clicked()
{
    command.append("#");
    command.append(ui->textEdit_3->toPlainText().toStdString()); //username
    command.append("#");
    command.append(ui->textEdit_4->toPlainText().toStdString()); //password
    m_client.write_to_sockfd(command);
    command.clear();
    ui->textEdit_3->clear();
    ui->textEdit_4->clear();
    //sleep(2);
    //ui->submitButton_2->disconnect();


    ui->label_3->hide();
    ui->label_4->hide();
    ui->textEdit_3->hide();
    ui->textEdit_4->hide();
    ui->pushButton_4->hide();
}
