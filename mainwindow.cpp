#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <dialogsetting.h>
#include <dialogcheckuser.h>

#include <qapplication.h>
#include "QMap"

typedef QMap<QString, QString> userList;

QString getRandomString()
{
   const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
   const int randomStringLength = 12; // assuming you want random strings of 12 characters

   QString randomString;
   for(int i=0; i<randomStringLength; ++i)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }
   return randomString;
}

userList getUsers() {
    QMap<QString, QString> users;
    users.insert("juw5B7nF7nJX", "Nguyễn Duy Hoàn");
    users.insert("r9JPFUjXaXS1", "Phạm Doãn Hiếu");
    users.insert("huWMxnHCTkc7", "Nguyễn Thị Thanh Tâm");

    return users;
}

QString findUser(QString code, userList users) {
    QString userName;

    foreach (QString key, users.keys()) {
        if (key == code) {
            userName = users[key];
            break;
        }
    }

    return userName;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setStyleSheet("background-color: white;");
    ui->setupUi(this);

    loadStyle();

    dialogSetting = new DialogSetting(this);
    dialogSetting->setWindowTitle("Cài đặt mở cửa");

    dialogCheckUser = new DialogCheckUser(this);
    dialogCheckUser->setWindowTitle("Thông báo");

    connect(dialogSetting, SIGNAL(on_changeOpenType(const QString&)), this, SLOT(changeOpenType(const QString&)));
    connect(dialogCheckUser, SIGNAL(on_openDoor(const QString&)), this, SLOT(openDoor(const QString&)));

    connect(this, SIGNAL(on_loadDefaultOpenType(const QString&)), dialogSetting, SLOT(loadValue(const QString&)));
    connect(this, SIGNAL(on_setUser(const QString&, const QString&)), dialogCheckUser, SLOT(setUser(const QString&, const QString&)));

    users = getUsers();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(closeDoor()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadStyle()
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

void MainWindow::toggleDoor1() {
    if (ui->btn_door_1->text() == "Mở cửa 1") {
        ui->btn_door_1->setText("Đóng cửa 1");
        ui->door_status_1->setStyleSheet("background-color: green;"
                                         "border-radius: 7;");
        ui->door_line_1->setStyleSheet("background-color: black;");
    } else {
        ui->btn_door_1->setText("Mở cửa 1");
        ui->door_status_1->setStyleSheet("background-color: red;"
                                         "border-radius: 7;");
    }
}

void MainWindow::toggleDoor2() {
    if (ui->btn_door_2->text() == "Mở cửa 2") {
        ui->btn_door_2->setText("Đóng cửa 2");
        ui->door_status_2->setStyleSheet("background-color: green;"
                                         "border-radius: 7;");
        ui->door_line_2->setStyleSheet("background-color: black;");
    } else {
        ui->btn_door_2->setText("Mở cửa 2");
        ui->door_status_2->setStyleSheet("background-color: red;"
                                         "border-radius: 7;");
    }
}

void MainWindow::openDoor(const QString& value){
    if (value == "door_1") {
        ui->btn_door_1->setText("Đóng cửa 1");
        ui->door_status_1->setStyleSheet("background-color: green;"
                                         "border-radius: 7;");
        ui->door_line_1->setStyleSheet("background-color: black;");
    } else if (value == "door_2") {
        ui->btn_door_2->setText("Đóng cửa 2");
        ui->door_status_2->setStyleSheet("background-color: green;"
                                         "border-radius: 7;");
        ui->door_line_2->setStyleSheet("background-color: black;");
    }

    timer->start(5000);
}

void MainWindow::closeDoor(){
    if (doorOpen == "door_1") {
        ui->btn_door_1->setText("Mở cửa 1");
        ui->door_status_1->setStyleSheet("background-color: red;"
                                         "border-radius: 7;");
        ui->door_line_1->setStyleSheet("background-color: black;");
    } else if (doorOpen == "door_2") {
        ui->btn_door_2->setText("Mở cửa 2");
        ui->door_status_2->setStyleSheet("background-color: red;"
                                         "border-radius: 7;");
        ui->door_line_2->setStyleSheet("background-color: black;");
    }
}

void MainWindow::on_btn_door_1_clicked()
{
    doorOpen = "door_1";
    QString code = "r9JPFUjXaXS1";

    QString userName = findUser(code, users);

    if (userName == nullptr) {
        return;
    }

    if (openType == "manual" && ui->btn_door_1->text() == "Mở cửa 1") {
        on_setUser(userName, doorOpen);
        dialogCheckUser->show();
        return;
    }

    toggleDoor1();
}

void MainWindow::on_btn_door_2_clicked()
{
    doorOpen = "door_2";
    QString code = "r9JPFUjXaXS1";

    QString userName = findUser(code, users);

    if (userName == nullptr) {
        return;
    }

    if (openType == "manual" && ui->btn_door_2->text() == "Mở cửa 2") {
        on_setUser(userName, doorOpen);
        dialogCheckUser->show();
        return;
    }

    toggleDoor2();
}

void MainWindow::on_btnSetting_clicked()
{
    dialogSetting->show();
    emit on_loadDefaultOpenType(openType);
}

void MainWindow::changeOpenType(const QString& value) {
    openType = value;
}
