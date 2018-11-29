#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<string>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    string on_submitButton_clicked();
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_calendarWidget_clicked();

    void on_timeEdit_timeChanged();

    void on_timeEdit_2_timeChanged();

    //string on_submitButton_clicked();

private:
    Ui::MainWindow *ui;
    string result;
};

#endif // MAINWINDOW_H
