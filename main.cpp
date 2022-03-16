#include "mainwindow.h"
#include <user.h>

#include "QMap"
#include <QDebug>
#include <QApplication>

typedef QMap<int,User*> userList;

userList getUsers()
{
    userList users;

    for (int i = 0; i < 5; i++) {
        User* user = new User();
        user -> setName("test test");
        user -> setCode("abcbac10292");

        users.insert(i, user);
    }

    return users;
}

User* findUser(QString code, userList users) {
    User* user;

    foreach (int key, users.keys()) {
        if (users.value(key)->code() == code) {
            user = users.value(key);
            break;
        }
    }

    return user;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(700, 500);
    w.show();

    userList users = getUsers();

    User* user = findUser("abcbac1029", users);

    return a.exec();
}
