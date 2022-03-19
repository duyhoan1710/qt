#include "dialogcheckuser.h"
#include "ui_dialogcheckuser.h"

#include <QDebug>

DialogCheckUser::DialogCheckUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCheckUser)
{
    ui->setupUi(this);
    ui->userLabel->setStyleSheet("qproperty-alignment: AlignCenter;");

    connect(ui->btnOpen, SIGNAL(clicked()), this, SLOT(on_btnOpen_clicked()));
}

DialogCheckUser::~DialogCheckUser()
{
    delete ui;
}

void DialogCheckUser::setUser(const QString& value, const QString& door) {
    m_door = door;
    QString label = "Có yêu cầu mở cửa từ ";
    ui->userLabel->setText(label.append(value).append(" (").append(door).append(")"));
}

void DialogCheckUser::on_btCancel_clicked()
{
    hide();
}

void DialogCheckUser::on_btnOpen_clicked()
{
    emit on_openDoor(m_door);
    hide();
}
