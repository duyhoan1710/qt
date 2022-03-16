#ifndef DIALOGSETTING_H
#define DIALOGSETTING_H

#include <QDialog>

namespace Ui {
class DialogSetting;
}

class DialogSetting : public QDialog
{
    Q_OBJECT

    QString m_openType;

public:
    explicit DialogSetting(QWidget *parent = nullptr);
    ~DialogSetting();

    QString getOpenType();
    void setOpenType(const QString &openType);

private slots:

    void on_exitBtn_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::DialogSetting *ui;
    void loadValue();
};

#endif // DIALOGSETTING_H
