#include "TcpServer.h"

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
    for (int port = 8081; port <= 8088; ++port) {
        QTcpServer *server = new QTcpServer(this);
        servers.append(server);

        // 当有新的连接时，调用 onNewConnection() 槽函数
        connect(server, &QTcpServer::newConnection, this, &TcpServer::onNewConnection);

        // 监听端口
        if (!server->listen(QHostAddress::Any, port)) {
            qCritical() << "Unable to start the server on port" << port << ":" << server->errorString();
            exit(EXIT_FAILURE);
        } else {
            qDebug() << "Server started on port" << port;
        }
    }
}

void TcpServer::onNewConnection() {
    QTcpServer *server = qobject_cast<QTcpServer*>(sender());

    if (server) {
        QTcpSocket *clientSocket = server->nextPendingConnection();
        qDebug() << "New connection from" << clientSocket->peerAddress().toString() << "on port" << server->serverPort();

        // 当有数据可读时，调用 onReadyRead() 槽函数
        connect(clientSocket, &QTcpSocket::readyRead, this, [=]() {
            QByteArray data = clientSocket->readAll();
            data1 =data;
            // 创建一个 uint8_t 向量来存储数据
            std::vector<uint8_t> uint8Vector(data.size());

            // 将 QByteArray 的数据复制到 uint8_t 向量中
            std::copy(data.begin(), data.end(), uint8Vector.begin());
            if(CheckXor(uint8Vector,8) == uint8Vector.at(8))
            {
                ClientData clientData;
                clientData.deviceNum = uint8Vector.at(2);
                clientData.isNowConcentration = uint8Vector.at(3);
                clientData.result = (uint8Vector[4]<<8)+uint8Vector[5];
                clientData.acquisitionInterval = uint8Vector.at(6);
                emit sendClientData(clientData);
                qDebug() << "Received:" << data<<" result:"<<clientData.result<<"  "<<QDateTime::currentDateTime().toString("mm:ss");
            }
        });

        // 当连接断开时，删除客户端套接字对象
        connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    }
}

void TcpServer::sendData(std::vector<uint8_t> data, int port) {
    for (QTcpServer *server : servers) {
        if (server->serverPort() == port) {
            QList<QTcpSocket*> clients = server->findChildren<QTcpSocket*>();
            for (QTcpSocket *clientSocket : clients) {
                if (clientSocket->state() == QAbstractSocket::ConnectedState) {
                    data[6]=CheckXor(data,6);
                    QByteArray byteArray(reinterpret_cast<const char*>(data.data()), data.size());
                    byteArray.append('\r');
                    clientSocket->write(byteArray);
                    qDebug() << "Sent data to port" << port;
                } else {
                    qWarning() << "Client on port" << port << "is not connected";
                }
            }
            return;
        }
    }
    qWarning() << "No server found on port" << port;
}

//异或校验 返回一个字节
uint8_t TcpServer::CheckXor(std::vector<uint8_t> vdata, int len)
{
    uint8_t checksum = 0;
    for (int i = 0;i < len;i++)
    {
        checksum = checksum ^ vdata[i];
    }
    return (uint8_t)checksum;
}
