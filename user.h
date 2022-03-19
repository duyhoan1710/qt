#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT

    QString m_name;

public:
    explicit User(QObject *parent = nullptr);
    ~User();

    QString name() const;
    void setName(const QString &name);

signals:

};

#endif // USER_H
