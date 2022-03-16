#include <user.h>

QString User::name() const {
    return m_name;
}

void User::setName(const QString &name) {
    m_name = name;
}

QString User::code() const {
    return m_code;
}

void User::setCode(const QString &code) {
    m_code = code;
}

User::User(QObject *parent) : QObject(parent) {}
User::~User(){}
