#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <dialogsetting.h>

#include <qapplication.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: white;");
    loadText();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadText()
{
    ui->door1_1->resize(10, 10);
    ui->door1_1->setStyleSheet("background-color: black;"
                               "border-radius: 5;"
                               );
    ui->door1_2->resize(10, 10);
    ui->door1_2->setStyleSheet("background-color: black;"
                               "border-radius: 5;"
                               );
    ui->door2_1->resize(10, 10);
    ui->door2_1->setStyleSheet("background-color: black;"
                               "border-radius: 5;"
                               );
    ui->door2_2->resize(10, 10);
    ui->door2_2->setStyleSheet("background-color: black;"
                               "border-radius: 5;"
                               );

    ui->door_line_1->setFixedHeight(1);
    ui->door_line_1->setStyleSheet("background-color: black;");

    ui->door_line_2->setFixedWidth(1);
    ui->door_line_2->setStyleSheet("background-color: black;");

    ui->door_status_1->resize(15, 15);
    ui->door_status_1->setStyleSheet("background-color: red;"
                                     "border-radius: 7");
    ui->door_status_2->resize(15, 15);
    ui->door_status_2->setStyleSheet("background-color: red;"
                                     "border-radius: 7");
}

void MainWindow::on_btn_door_1_clicked()
{
    if (ui->btn_door_1->text() == "open door 1") {
        ui->btn_door_1->setText("close door 1");
        ui->door_status_1->setStyleSheet("background-color: green;"
                                         "border-radius: 7;");
        ui->door_line_1->setStyleSheet("background-color: black;");
    } else {
        ui->btn_door_1->setText("open door 1");
        ui->door_status_1->setStyleSheet("background-color: red;"
                                         "border-radius: 7;");
    }

}

void MainWindow::on_btnSetting_clicked()
{
    dialogSetting = new DialogSetting(this);
    dialogSetting->setWindowTitle("Setting Open Door");
    dialogSetting->show();
}
