#ifndef REMOTECONTROLLER_H
#define REMOTECONTROLLER_H

#include <QObject>
#include <QMainWindow>
#include "packet.h"
#include "remoteclient.h"
#include "watchdialog.h"
#include "tcpclient.h"

class RemoteController : public QObject
{
    Q_OBJECT
public:
    static RemoteController* GetInstance();
    void Init();
    bool SendCommandPacket(int cmd,
                           bool autoClose = true,
                           BYTE* pData = NULL,
                           size_t nLength = 0);
private:
    explicit RemoteController(QObject *parent = nullptr);
    ~RemoteController();

    class Helper
    {
    public:
        Helper()
        {
            RemoteController::GetInstance();
        }
        ~Helper()
        {
            RemoteController::GetInstance()->~RemoteController();
        }
    };

private:
    static  Helper m_helper;
    static RemoteController* m_instance;
    RemoteClient* m_clientDlg;
    WatchDialog*  m_watchDlg;
    TcpClient*    m_tcpClient;
};

#endif // REMOTECONTROLLER_H
