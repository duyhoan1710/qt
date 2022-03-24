#include "myserver.h"
#include "QWebSocket"

WebServer::WebServer(QObject *parent) :
    QWebSocketServer("MiServidor", QWebSocketServer::NonSecureMode, parent)
{
    server = NULL;
    connect(this, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

void WebServer::newConnection() {
    server = nextPendingConnection();
    connect(server, SIGNAL(textMessageReceived(const QString&)), this, SLOT(receiveData(const QString&)));
}

void WebServer::receiveData(const QString& message) {
    emit on_receiveData(message);
}
