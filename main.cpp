#include "remoteclient.h"
#include "remotecontroller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    RemoteClient w;
//    w.show();

    RemoteController* s = RemoteController::GetInstance();
    s->Init();
    return a.exec();
}
