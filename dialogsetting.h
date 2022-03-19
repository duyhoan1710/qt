#ifndef DIALOGSETTING_H
#define DIALOGSETTING_H

#include <QDialog>

namespace Ui {
class DialogSetting;
}

class DialogSetting : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSetting(QWidget *parent = nullptr);
    ~DialogSetting();

private slots:
    void on_exitBtn_clicked();
    void on_btnSaveSetting_clicked();
    void loadValue(const QString&);

signals:
    void on_changeOpenType(const QString&);

private:
    Ui::DialogSetting *ui;
};

#endif // DIALOGSETTING_H
