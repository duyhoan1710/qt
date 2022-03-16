#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <dialogsetting.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_door_1_clicked();

    void on_btnSetting_clicked();

private:
    Ui::MainWindow *ui;
    DialogSetting *dialogSetting;
    QGraphicsScene *scene;
    QGraphicsLineItem *line;
    QGraphicsRectItem *rectangle;
    void loadText();
};
#endif // MAINWINDOW_H
