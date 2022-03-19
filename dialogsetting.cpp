#include "dialogsetting.h"
#include "ui_dialogsetting.h"
#include <mainwindow.h>

#include "QDebug"

DialogSetting::DialogSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSetting)
{
    ui->setupUi(this);
    connect(ui->btnSaveSetting, SIGNAL(clicked()), this, SLOT(on_btnSaveSetting_clicked()));

}

DialogSetting::~DialogSetting()
{
    delete ui;
}

void DialogSetting::loadValue(const QString& value)
{
    if (value == "auto") {
        ui->radio_auto->setChecked(true);
    } else if (value == "manual") {
        ui->radio_manual->setChecked(true);
    }
}

void DialogSetting::on_exitBtn_clicked()
{
    hide();
}

void DialogSetting::on_btnSaveSetting_clicked()
{
    QString value;

    if (ui->radio_auto->isChecked()) {
        value = "auto";
    } else if (ui->radio_manual->isChecked()) {
        value = "manual";
    }

    emit on_changeOpenType(value);
    hide();
}

