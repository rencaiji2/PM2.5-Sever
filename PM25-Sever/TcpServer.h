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
#include "QThread"
#include <QMutex>

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);

    void sendData(std::vector<uint8_t> data, int port);

    static TcpServer* getInstance() {
            static QMutex mutex;
            if (!instance) {
                QMutexLocker locker(&mutex);
                if (!instance) {
                    instance = new TcpServer();
                }
            }
            return instance;
        }

signals:
    void sendClientData(ClientData data);

private slots:
    void onNewConnection();

private:
    uint8_t CheckXor(std::vector<uint8_t> vdata, int len);

    QList<QTcpServer*> servers;

    QByteArray data1;

    static TcpServer* instance; // 静态指针，保存单例实例
};

#endif // TCPSERVER_H
