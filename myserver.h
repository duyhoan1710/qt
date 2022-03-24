#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QWebSocketServer>

class WebServer : public QWebSocketServer
{
    Q_OBJECT
public:
    explicit WebServer(QObject *parent = 0);

signals:
    void on_receiveData(const QString&);

private slots:
    void newConnection();
    void receiveData(const QString&);

private:
    QWebSocket *server;
};

#endif // MYSERVER_H
