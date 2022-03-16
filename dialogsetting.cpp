#include "dialogsetting.h"
#include "ui_dialogsetting.h"

#include "QDebug"

DialogSetting::DialogSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSetting)
{
    ui->setupUi(this);
    loadValue();
}

DialogSetting::~DialogSetting()
{
    delete ui;
}

QString DialogSetting::getOpenType(){
    return m_openType;
}

void DialogSetting::setOpenType(const QString &openType) {
    m_openType = openType;
}

void DialogSetting::loadValue()
{
    ui->radio_auto->setChecked(true);
}

void DialogSetting::on_exitBtn_clicked()
{
    hide();
}

void DialogSetting::on_pushButton_2_clicked()
{
    if (ui->radio_auto->isChecked()) {
        qInfo() << "auto";
    } else {
        qInfo() << "manual";
        m_openType = "manual";
    }

    qInfo() << m_openType;
}
