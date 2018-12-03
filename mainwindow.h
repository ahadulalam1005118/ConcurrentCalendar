#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<string>
#include "client.h"
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    client m_client;
    //void on_submitButton_clicked();
    explicit MainWindow(client m_client, QWidget *parent = 0);
   // explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_calendarWidget_clicked();

    void on_timeEdit_timeChanged();

    void on_timeEdit_2_timeChanged();

    void on_submitButton_clicked();

    void on_refreshButton_clicked();

private:
    Ui::MainWindow *ui;
    QString result;
};

#endif // MAINWINDOW_H
