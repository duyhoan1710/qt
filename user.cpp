#include <user.h>

QString User::name() const {
    return m_name;
}

void User::setName(const QString &name) {
    m_name = name;
}

User::User(QObject *parent) : QObject(parent) {}
User::~User(){}
