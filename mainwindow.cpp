#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include<string>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

string MainWindow::on_submitButton_clicked()
{
    result += ui->calendarWidget->selectedDate().toString("dd/MM/yy").toStdString();
    result += "|";
    result += ui->timeEdit->time().toString("hh:mm:ss").toStdString();
    result += "|";
    result += ui->timeEdit_2->time().toString("hh:mm:ss").toStdString();
    result += "|";
    result += ui->textEdit->toPlainText().toStdString();
    result += "|";
    //ui->textEdit_2->setText(result);
    return result;
}
