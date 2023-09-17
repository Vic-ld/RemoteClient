#ifndef REMOTECLIENT_H
#define REMOTECLIENT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class RemoteClient; }
QT_END_NAMESPACE

class RemoteClient : public QMainWindow
{
    Q_OBJECT

public:
    RemoteClient(QWidget *parent = nullptr);
    ~RemoteClient();
signals:
    void updateHost(QString ip,QString port);

private slots:
    void on_btnConnect_clicked();

private:
    Ui::RemoteClient *ui;
};
#endif // REMOTECLIENT_H
