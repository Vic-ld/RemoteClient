#include "remotecontroller.h"

RemoteController *RemoteController::GetInstance()
{
    if (m_instance == NULL)
    {
        m_instance = new RemoteController();
    }
    return m_instance;
}

RemoteController::RemoteController(QObject *parent)
{

}

void RemoteController::Init()
{
    m_clientDlg = new RemoteClient();
    m_watchDlg  = new WatchDialog();
    m_tcpClient = new TcpClient();

    connect(m_clientDlg,&RemoteClient::updateHost,m_tcpClient,&TcpClient::SetHost);
    m_clientDlg->show();
}

bool RemoteController::SendCommandPacket(int cmd, bool autoClose, BYTE *pData, size_t nLength)
{
    Packet packet(cmd,pData,nLength);
    m_tcpClient->InitSocket();
    m_tcpClient->Send(packet);
    return true;
}

RemoteController::~RemoteController()
{
    delete m_clientDlg;
    delete m_watchDlg;
    delete m_tcpClient;
}

RemoteController* RemoteController::m_instance = NULL;
RemoteController* ctrl = RemoteController::GetInstance();
RemoteController::Helper RemoteController::m_helper;
