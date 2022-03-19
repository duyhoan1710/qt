#ifndef DIALOGCHECKUSER_H
#define DIALOGCHECKUSER_H

#include <QDialog>

namespace Ui {
class DialogCheckUser;
}

class DialogCheckUser : public QDialog
{
    Q_OBJECT
    QString m_door;

public:
    explicit DialogCheckUser(QWidget *parent = nullptr);
    ~DialogCheckUser();

private slots:
    void setUser(const QString&, const QString&);

    void on_btCancel_clicked();
    void on_btnOpen_clicked();

signals:
    void on_openDoor(const QString&);

private:
    Ui::DialogCheckUser *ui;
};

#endif // DIALOGCHECKUSER_H
