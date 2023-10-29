#include <QCoreApplication>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include "myobject.h"
#include "globalstatus.h"



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

#ifdef ZERO1
    {
        auto myobject = new MyObject();
        auto child1 [[maybe_unused]] = new MyObject(myobject);
        auto *child2 = new MyObject(myobject);
        auto *child3 = new MyObject(myobject);
        delete myobject;
    }
#endif

#define ZERO2
#ifdef ZERO2
    {
        auto myobject = new MyObject();
        myobject->setObjectName("my object123");
        qInfo() << "hello";
        auto globalStatus = GlobalStatus::getInstance();
        QObject::connect(globalStatus, &GlobalStatus::statusKeyChanged, [=] {
            qInfo() << "status has changed to: " << GlobalStatus::getInstance()->statusKey();
        });
        QObject::connect(globalStatus, &GlobalStatus::statusKeyChanged, myobject, &MyObject::dumpMe);
        QObject::connect(globalStatus, &GlobalStatus::statusKeyChangedWithStatusKey, myobject, &MyObject::dumpMeWithArgument);
        globalStatus->setStatusKey("status.started");
        globalStatus->setStatusKey("status.stopped");
    }

#endif

    QTimer::singleShot(1, &a, [&]() {
        a.exit(0);
    });
    return a.exec();
}
