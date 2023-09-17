#include "remoteclient.h"
#include "remotecontroller.h"

#include "ui_remoteclient.h"

RemoteClient::RemoteClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RemoteClient)
{
    ui->setupUi(this);
}

RemoteClient::~RemoteClient()
{
    delete ui;
}

void RemoteClient::on_btnConnect_clicked()
{
    emit updateHost(ui->lineHost->text(),ui->linePort->text());
    RemoteController* ctrl = RemoteController::GetInstance();
    ctrl->SendCommandPacket(1987);
}

