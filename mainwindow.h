#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <dialogsetting.h>
#include <dialogcheckuser.h>

#include <user.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef QMap<QString,QString> userList;

class WebServer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QString openType = "manual";
    QString doorOpen;
    userList users;
    QTimer *timer;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_door_1_clicked();
    void on_btn_door_2_clicked();

    void on_btnSetting_clicked();
    void changeOpenType(const QString&);

     void openDoor(const QString&);
     void closeDoor();
     void receiveData(const QString&);


signals:
    void on_loadDefaultOpenType (const QString&);
    void on_setUser(const QString&, const QString&);

private:
    Ui::MainWindow *ui;
    DialogSetting *dialogSetting;
    DialogCheckUser * dialogCheckUser;
    void loadStyle();
    void toggleDoor1();
    void toggleDoor2();
    WebServer *server;
    void scanDoor1(const QString&);
    void scanDoor2(const QString&);
    void notFoundUser(const QString&);
};
#endif // MAINWINDOW_H
