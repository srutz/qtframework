#include <QCoreApplication>
#include <QDebug>
#include <QMetaProperty>
#include "volumecontrol.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto vc = new VolumeControl();
    vc->connect(vc, &VolumeControl::volumeChanged, [=](double newVolume) {
        qInfo() << "new volumne: " << newVolume;
    });

    qInfo() << *vc;
    vc->setVolume(20);

    auto mo = vc->metaObject();
    qInfo() << "classname: " << mo->className();
    for (int i = 0, n = mo->propertyCount(); i < n; i++) {
        auto prop = mo->property(i);
        qInfo() << "property: " << prop.name() << ", value=" << prop.read(vc);
    }

    return 0;
    //return a.exec();
}
