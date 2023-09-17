#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include "packet.h"

#include <QObject>
#include <QTcpSocket>
namespace
{
    const int BUFFER_SIZE  = 4096000;
}
class TcpClient: public QObject
{
    Q_OBJECT
public:
    bool InitSocket();
    bool Send(const char* pData, int nSize);
    bool Send(const Packet& pack);
    int DealCommand();
    inline Packet& GetPacket(){return m_packet;};
    void SetHost(QString ip,QString port);
    void CloseSocket();

private slots:
    void receivedData();

public:
    TcpClient& operator=(const TcpClient& ss) {Q_UNUSED(ss)  return *this;};
    TcpClient()
    {
        m_addr = "127.0.0.1";
        m_port = 9527;
        m_tcpSocket = new QTcpSocket();
        m_buffer.resize(::BUFFER_SIZE);
        memset(m_buffer.data(), 0, ::BUFFER_SIZE);
       // QObject::connect(m_tcpSocket, &QTcpSocket::readyRead, this, &TcpClient::receivedData);
    };
    ~TcpClient()
    {
        m_tcpSocket->close();
    };

private:
    std::vector<char> m_buffer;
    QTcpSocket *m_tcpSocket;
    QString m_addr;
    unsigned short m_port;
    Packet  m_packet;
};

#endif // TCPCLIENT_H
