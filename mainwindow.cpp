#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <dialogsetting.h>
#include <dialogcheckuser.h>

#include <qapplication.h>
#include "QMap"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <myserver.h>

typedef QMap<QString, QString> userList;

QString pathFileOpenErrorDoor1 = "/home/hoannguyen/Desktop/qt/openDoor1Error.txt";
QString pathFileOpenErrorDoor2 = "/home/hoannguyen/Desktop/qt/openDoor2Error.txt";

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

    server = new WebServer(this);
    server->listen(QHostAddress::Any, 8080);

    connect(server, SIGNAL(on_receiveData(const QString&)), this, SLOT(receiveData(const QString&)));
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

void writeHistoryOpenDoor() {
    QFile file("/home/parallels/test/history.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << "This file is generated by Qt\n";

    file.close();
}

void readHistoryOpenDoor(){
    QFile file("/home/parallels/test/history.txt");

    QTextStream in(&file);



    if(!file.open(QIODevice::ReadOnly)) {
        qInfo("error");
    }

    while(!in.atEnd()) {
        QString line = in.readLine();

        qInfo() << line;
    }

    file.close();
}

void writeFileOpenError(const QString& pathFile, const QString& value, const QString& count) {
    QFile file(pathFile);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << value;
    out << "-";
    out << count;

    file.close();
}

QString readFileOpenError(const QString& pathFile) {
    QFile file(pathFile);
    QTextStream in(&file);
    QString text = "";

    file.open(QIODevice::ReadOnly);

    while(!in.atEnd()) {
        QString line = in.readLine();
        text = line;
    }
    file.close();

    return text;
}

void clearFileOpenError(const QString& pathFile) {
    QFile file(pathFile);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << "";

    file.close();
}

void MainWindow::notFoundUser(const QString& filePath) {
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("yyyy.MM.dd hh:mm:ss");
    QString count = "1";
    QString fileDateTime = "";

    QString dataFile = readFileOpenError(filePath);

    if (dataFile != "") {
        count = QString::number(dataFile.right(1).toInt() + 1);
        fileDateTime = dataFile.left(19);
    }

    if (date.secsTo(QDateTime::fromString(fileDateTime, "yyyy.MM.dd hh:mm:ss")) >= -30){
        writeFileOpenError(filePath, formattedTime, count);

        if (count.toInt() > 3) {
            QString noti = "Thông báo ";
            QString text = "Có người đang mở cửa với thẻ không hợp lệ";

            QMessageBox::warning(this, noti, text.append(" (").append(doorOpen).append(")"));
        }
    } else {
        writeFileOpenError(filePath, formattedTime, "1");
    }
}

void MainWindow::receiveData(const QString& value) {
    QString door = value.left(6);
    QString code = value.right(12);

    qInfo() << value;

    QString userName = findUser(code, users);

    if (door != "door_1" && door != "door_2") {
        return;
    }

    if (door == "door_1") {
        scanDoor1(code);
    }
    else if (door == "door_2") {
        scanDoor2(code);
    }
}

void MainWindow::on_btn_door_1_clicked()
{
    toggleDoor1();
}

void MainWindow::scanDoor1(const QString& code) {
    doorOpen = "door_1";

    QString userName = findUser(code, users);

    if (userName == nullptr) {
        notFoundUser(pathFileOpenErrorDoor1);
        return;
    }

    if (ui->btn_door_1->text() == "Mở cửa 1") {
        writeFileOpenError(pathFileOpenErrorDoor1, "", "");
    }

    if (openType == "manual" && ui->btn_door_1->text() == "Mở cửa 1") {
        on_setUser(userName, doorOpen);
        dialogCheckUser->show();
        return;
    }

    openDoor(doorOpen);
}

void MainWindow::scanDoor2(const QString& code) {
    doorOpen = "door_2";
    QString userName = findUser(code, users);

    if (userName == nullptr) {
        notFoundUser(pathFileOpenErrorDoor2);
        return;
    }

    if (ui->btn_door_1->text() == "Mở cửa 2") {
        writeFileOpenError(pathFileOpenErrorDoor2, "", "");
    }

    if (openType == "manual" && ui->btn_door_2->text() == "Mở cửa 2") {
        on_setUser(userName, doorOpen);
        dialogCheckUser->show();
        return;
    }

    openDoor(doorOpen);
}

void MainWindow::on_btn_door_2_clicked()
{
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
