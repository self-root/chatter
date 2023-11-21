#include "socketconnection.h"

namespace Chatter {
SocketConnection::SocketConnection(const QString &serverAddess, int port_, QObject *parent)
    : QObject{parent}, chatServerAddress(serverAddess), port(port_)
{

}

void SocketConnection::init()
{
    clientConnection = new QTcpSocket(this);
    connect(clientConnection, &QTcpSocket::connected, this, &SocketConnection::clientConnected);
    connect(clientConnection, &QTcpSocket::disconnected, this, &SocketConnection::clientDisconnected);
    connect(clientConnection, &QTcpSocket::readyRead, this, &SocketConnection::clientReadyRead);
    connect(clientConnection, &QTcpSocket::stateChanged, this, &SocketConnection::onStateChanged);
    connect(clientConnection, &QTcpSocket::errorOccurred, this, &SocketConnection::onError);
    connect(&connectTimer, &QTimer::timeout, this, &SocketConnection::startConnection);
}

void SocketConnection::startConnection()
{
    clientConnection->connectToHost(QHostAddress(chatServerAddress), port);
}

int SocketConnection::send(const QByteArray &data)
{
    int messageLen = data.size();
    std::string l = std::to_string(messageLen);
    QByteArray lenPacket;
    lenPacket.fill('\0', (7 - l.size()));
    lenPacket.insert(0, l.c_str());
    lenPacket.append(data);
    int byteSent = clientConnection->write(lenPacket);
    return byteSent;
}


void SocketConnection::clientConnected()
{
    if (connectTimer.isActive())
        connectTimer.stop();
}

/**
 * @brief SocketConnection::clientDisconnected
 * Try to reconnect to the server every 2 seconds
 */
void SocketConnection::clientDisconnected()
{
    connectTimer.start(2000);
}

/**
 * @brief SocketConnection::clientReadyRead
 * The first 7 bytes contains the size of the data
 */
void SocketConnection::clientReadyRead()
{
    int dataLength = clientConnection->read(7).toInt();
    QByteArray data;
    int byteRead = 0;

    while (byteRead < dataLength)
    {
        QByteArray chunc = clientConnection->read(std::min(dataLength - byteRead, 2048));
        byteRead = byteRead + chunc.length();
        data.append(chunc);
    }
    emit dataReceived(data);
    if (clientConnection->bytesAvailable() > 0)
        clientReadyRead();
}

void SocketConnection::onError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "ConnectionRefusedError";
        if (!connectTimer.isActive())
            connectTimer.start(2000);
        break;
    case QAbstractSocket::SocketTimeoutError:
        qDebug() << "SocketTimeoutError";
        if (!connectTimer.isActive())
            connectTimer.start(2000);
        break;
    default:
        qDebug() << "Another socket error: " << socketError;
        qDebug() << "Available bytes: " << clientConnection->bytesAvailable();
        qDebug() << "Byte to write: " << clientConnection->bytesToWrite();
        //clientConnection->abort();
        break;
    }
}

void SocketConnection::onStateChanged(QAbstractSocket::SocketState socketState)
{
    switch (socketState) {
    case QAbstractSocket::ConnectingState:
        if (connectTimer.isActive())
            connectTimer.stop();
        break;
    case QAbstractSocket::HostLookupState:
        qDebug() << "[Socket] HostLookupState";
        break;
    case QAbstractSocket::ClosingState:
        qDebug() << "[Socket] ClosingState";
        break;
    default:
        break;
    }
}
}

