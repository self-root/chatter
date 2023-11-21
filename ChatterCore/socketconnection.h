#ifndef SOCKETCONNECTION_H
#define SOCKETCONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include "chattercore_global.h"

namespace Chatter {
/**
 * @brief The SocketConnection class handle sending and receiving data to the chat server
 */
class CHATTERCORE_EXPORT SocketConnection : public QObject
{
    Q_OBJECT
public:
    explicit SocketConnection(const QString &serverAddess, int port_, QObject *parent = nullptr);
public slots:
    void init();
    void startConnection();
    /**
     * @brief send: Send data to the server. The data length will be added
     * at the begining of the packet(first 7 bytes)
     * @param data: QByteArray, the data to be sent
     * @return the size of the packet sent
     */
    int send(const QByteArray &data);
private:
    QString chatServerAddress;
    int port;
    QTcpSocket *clientConnection = nullptr;
    QTimer connectTimer;

private slots:
    void clientConnected();
    void clientDisconnected();
    void clientReadyRead();
    void onError(QAbstractSocket::SocketError socketError);
    void onStateChanged(QAbstractSocket::SocketState socketState);

signals:
    void dataReceived(const QByteArray &data);
};
}


#endif // SOCKETCONNECTION_H
