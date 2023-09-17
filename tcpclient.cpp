#include "tcpclient.h"

#include <QAbstractSocket>
#include <qmessagebox.h>

bool TcpClient::InitSocket()
{
    //qDebug() << __LINE__ << m_tcpSocket->isValid();
    if (m_tcpSocket->isValid())
    {
        m_tcpSocket->close();
    }
    //qDebug() << __LINE__ << m_tcpSocket->isValid();
    m_tcpSocket->connectToHost(m_addr,m_port);
    if(m_tcpSocket->waitForConnected(50))
    {
        qDebug() << "连接服务器成功!";
        return true;
    }
    return false;
}

bool TcpClient::Send(const char *pData, int nSize)
{
    if(!m_tcpSocket->isValid())
    {
        return false;
    }
    return m_tcpSocket->write(pData,nSize) > 0;
}

bool TcpClient::Send(const Packet &pack)
{
    if(!m_tcpSocket->isValid())
    {
        return false;
    }
    string strOut;
    pack.Data(strOut);
    //return m_tcpSocket->write(strOut.c_str(), strOut.size()) > 0;
    bool ret = m_tcpSocket->write(strOut.c_str(), strOut.size()) > 0;
    m_tcpSocket->flush();
    return ret;
}


int TcpClient::DealCommand()
{
    char* buffer = m_buffer.data();
    static size_t index = 0;
    while (true)
    {
        if((m_tcpSocket->waitForReadyRead()) == false && ((int)index <= 0))
        {
            qDebug()<<tr("Server does not response!");
            return -1;
        }

        size_t len = m_tcpSocket->read(buffer + index, ::BUFFER_SIZE - index);
        if ((int)len <= 0 && (int)index <= 0)
            return -1;
        if((int)len >=0)
        {
            index += len;
        }
        len = index;
        //qDebug()<<len;
        m_packet = Packet((BYTE*)buffer, len);
        //qDebug() <<"packet data:"<< m_packet.strData.c_str();
        if (len > 0)
        {
            memmove(buffer, buffer + len, index - len);
            index -= len;
            //qDebug() <<"receieve packet index after:"<<index;
            //qDebug() <<"CMD:"<<m_packet.sCmd;
            return m_packet.sCmd;
        }

    }
    //qDebug()<<"exit";
    return -1;
}

void TcpClient::SetHost(QString ip,QString port)
{
    m_addr = ip;
    m_port = port.toUShort();
}

void TcpClient::CloseSocket()
{
    m_tcpSocket->close();
}

void TestConnection()
{

}

void TcpClient::receivedData()
{
    static int count = 0;
    int ret = DealCommand();
    qDebug()<<"receive data："<<m_packet.strData.c_str();
    qDebug()<<"receive count :" << ++count;
    switch(ret)
    {
    case 1:
        break;
    case 2023:
        TestConnection();
        break;
    default:
        break;
    }
    return;
}

