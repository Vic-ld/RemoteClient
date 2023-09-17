#ifndef WATCHDIALOG_H
#define WATCHDIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include "packet.h"

namespace Ui {
class WatchDialog;
}

class WatchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WatchDialog(QWidget *parent = nullptr);
    ~WatchDialog();
    void SetImg(QImage &);
    QPoint UserPoint2RemotePoint(QPoint);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event)override;
    void wheelEvent(QWheelEvent *event)override;

private:
    Ui::WatchDialog *ui;
};

#endif // WATCHDIALOG_H
