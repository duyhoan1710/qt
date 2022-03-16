#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT

    QString m_name;
    QString m_code;

public:
    explicit User(QObject *parent = nullptr);
    ~User();

    QString name() const;
    void setName(const QString &name);

    QString code() const;
    void setCode(const QString &code);

signals:

};

#endif // USER_H
