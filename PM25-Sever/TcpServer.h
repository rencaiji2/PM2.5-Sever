#ifndef TCPSERVER_H
#define TCPSERVER_H
#include "QObject"
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include "QDebug"
#include <QList>
#include "PublicStruct.h"
#include <QDateTime>

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);

    void sendData(std::vector<uint8_t> data, int port);

signals:
    void sendClientData(ClientData data);

private slots:
    void onNewConnection();

private:
    uint8_t CheckXor(std::vector<uint8_t> vdata, int len);

    QList<QTcpServer*> servers;

    QByteArray data1;
};

#endif // TCPSERVER_H
