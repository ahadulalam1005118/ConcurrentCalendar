#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include<string>
#include <unistd.h>

using namespace std;

MainWindow::MainWindow(client m_client,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->m_client = m_client;

    //this->m_client.write_to_sockfd("abc");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calendarWidget_clicked()
{
    //result += ui->calendarWidget->selectedDate().toString("dd/MM/yy");
    //result += "|";
    //ui->textEdit_2->setText(ui->calendarWidget->selectedDate().toString("dd/MM/yy"));
}


void MainWindow::on_timeEdit_timeChanged() //start
{
   // QTime time1 = ui->timeEdit->time();
    //result += ui->timeEdit->time().toString("hh:mm:ss");
    //result += "|";

    //ui->textEdit_2->setText(ui->timeEdit->time().toString("hh:mm:ss.zzz"));

}

void MainWindow::on_timeEdit_2_timeChanged()//end time
{
    //result += ui->timeEdit_2->time().toString("hh:mm:ss");
   // result += "|";
    //ui->textEdit_2->setText(ui->timeEdit_2->time().toString("hh:mm:ss.zzz"));
}

void MainWindow::on_submitButton_clicked()
{
    //this->m_client.write_to_sockfd("abc");
    this->result += ui->calendarWidget->selectedDate().toString("dd/MM/yy");
    this->result += "|";
    this->result += ui->timeEdit->time().toString("hh:mm:ss");
    this->result += "|";
    this->result += ui->timeEdit_2->time().toString("hh:mm:ss");
    this->result += "|";
    this->result += ui->textEdit->toPlainText();
    this->result += "|";
    string to_send = "data#"+result.toStdString();
    this->m_client.write_to_sockfd(to_send);
    //ui->textEdit_2->setText(this->result);
    vector<event_info> events = m_client.get_events();
    //cout << "sz" << events.size() << endl;
        //ui->textEdit_2->append("");
        ui->textEdit_2->insertPlainText("Name");
        ui->textEdit_2->insertPlainText(QString( 10, ' ' ));
        ui->textEdit_2->insertPlainText("Event");
        ui->textEdit_2->insertPlainText(QString( 10, ' ' ));
        ui->textEdit_2->insertPlainText("Date");
        ui->textEdit_2->insertPlainText(QString( 10, ' ' ));
        ui->textEdit_2->insertPlainText("Start");
        ui->textEdit_2->insertPlainText(QString( 10, ' ' ));
        ui->textEdit_2->insertPlainText("End");
        ui->textEdit_2->insertPlainText(QString( 10, ' ' ));
        for(int cnt =0; cnt < events.size(); cnt++) {
            QString qname = QString::fromStdString(events[cnt].hostname);
            QString qdate = QString::fromStdString(events[cnt].date);
            QString qstart_time = QString::fromStdString(events[cnt].start_time);
            QString qend_time = QString::fromStdString(events[cnt].end_time);
            QString qevent_desc = QString::fromStdString(events[cnt].event_desc);

            //cout << events[cnt].date<< endl;
             ui->textEdit_2->append("");
            ui->textEdit_2->insertPlainText(qname);
            ui->textEdit_2->insertPlainText(QString( 4, ' ' ));
            ui->textEdit_2->insertPlainText(qevent_desc);
            ui->textEdit_2->insertPlainText(QString( 4, ' ' ));
            ui->textEdit_2->insertPlainText(qdate);
            ui->textEdit_2->insertPlainText(QString( 4, ' ' ));
            ui->textEdit_2->insertPlainText(qstart_time);
            ui->textEdit_2->insertPlainText(QString( 4, ' ' ));
            ui->textEdit_2->insertPlainText(qend_time);
            ui->textEdit_2->insertPlainText(QString( 4, ' ' ));


        }
        //sleep(5);




    //return result;
}

void MainWindow::on_refreshButton_clicked()
{
    ui->textEdit_2->clear();
    vector<event_info> events = m_client.get_events();
    //cout << "sz" << events.size() << endl;
        //ui->textEdit_2->append("");
        ui->textEdit_2->insertPlainText("Name");
        ui->textEdit_2->insertPlainText(QString( 10, ' ' ));
        ui->textEdit_2->insertPlainText("Event");
        ui->textEdit_2->insertPlainText(QString( 10, ' ' ));
        ui->textEdit_2->insertPlainText("Date");
        ui->textEdit_2->insertPlainText(QString( 10, ' ' ));
        ui->textEdit_2->insertPlainText("Start");
        ui->textEdit_2->insertPlainText(QString( 10, ' ' ));
        ui->textEdit_2->insertPlainText("End");
        ui->textEdit_2->insertPlainText(QString( 10, ' ' ));
        for(int cnt =0; cnt < events.size(); cnt++) {
            QString qname = QString::fromStdString(events[cnt].hostname);
            QString qdate = QString::fromStdString(events[cnt].date);
            QString qstart_time = QString::fromStdString(events[cnt].start_time);
            QString qend_time = QString::fromStdString(events[cnt].end_time);
            QString qevent_desc = QString::fromStdString(events[cnt].event_desc);

            //cout << events[cnt].date<< endl;
             ui->textEdit_2->append("");
            ui->textEdit_2->insertPlainText(qname);
            ui->textEdit_2->insertPlainText(QString( 4, ' ' ));
            ui->textEdit_2->insertPlainText(qevent_desc);
            ui->textEdit_2->insertPlainText(QString( 4, ' ' ));
            ui->textEdit_2->insertPlainText(qdate);
            ui->textEdit_2->insertPlainText(QString( 4, ' ' ));
            ui->textEdit_2->insertPlainText(qstart_time);
            ui->textEdit_2->insertPlainText(QString( 4, ' ' ));
            ui->textEdit_2->insertPlainText(qend_time);
            ui->textEdit_2->insertPlainText(QString( 4, ' ' ));

        }

}
