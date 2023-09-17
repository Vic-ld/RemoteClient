#include "watchdialog.h"
#include "ui_watchdialog.h"

WatchDialog::WatchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WatchDialog)
{
    ui->setupUi(this);

}

WatchDialog::~WatchDialog()
{
    delete ui;
}

void WatchDialog::SetImg(QImage &receivedImage)
{
    ui->label->setPixmap(QPixmap::fromImage(receivedImage));
    ui->label->update();
    //qDebug() << "update imag";
}

QPoint WatchDialog::UserPoint2RemotePoint(QPoint localPos)
{
    QPoint remotePos;
    remotePos.setX(localPos.x()*1920/1200);
    remotePos.setY(localPos.y()*1080/675);
    return remotePos;
}

void WatchDialog::mousePressEvent(QMouseEvent *event)
{
    qDebug() <<QString("Mouse Pressed: (%1, %2)").arg(event->x()).arg(event->y());
    QRect dialogRect = this->geometry();
    if (dialogRect.contains(event->pos()))
    {
        qDebug() << dialogRect;
    }
    else
    {
        qDebug() << "Mouse clicked outside the dialog.";
        return;
    }
    if (event->button() == Qt::LeftButton)
    {
        MOUSEEV mevent;
        QPoint remote = UserPoint2RemotePoint(event->pos());
        mevent.x = remote.x();
        mevent.y = remote.y();
        mevent.nButton = 1;//左键
        mevent.nAction = 2;//按下
//        MainWindow *win = (MainWindow *)parent();

//        BYTE* byte = new BYTE[sizeof(mevent)];
//        memcpy(byte, &mevent, sizeof(mevent));
//        MOUSEEV test;
//        memcpy(&test, byte, sizeof(test));

//        win->SendCommandPacket(5,false,(BYTE*)&mevent,sizeof(mevent));
        qDebug() << "Left Mouse Button Pressed";
        qDebug() <<QString("Mouse Pressed: (%1, %2)").arg(event->x()).arg(event->y());
    }
    else if (event->button() == Qt::RightButton)
    {
        qDebug() << "Right Mouse Button Pressed";
    }
    else if (event->button() == Qt::MiddleButton)
    {
        qDebug() << "Middle Mouse Button Pressed";
    }
}

void WatchDialog::mouseReleaseEvent(QMouseEvent *event)
{

}

void WatchDialog::mouseMoveEvent(QMouseEvent *event)
{

}

void WatchDialog::mouseDoubleClickEvent(QMouseEvent *event)
{

}

void WatchDialog::wheelEvent(QWheelEvent *event)
{
//    QString mouseEventInfo = QString("Mouse Pressed: (%1, %2)").arg(event->x()).arg(event->y());
//    qDebug() << mouseEventInfo;
}
