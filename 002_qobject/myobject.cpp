#include "myobject.h"

MyObject::MyObject(QObject *parent) : QObject{parent}
{
    qInfo() << "MyObject()";

}

MyObject::~MyObject() {
    qInfo() << "~MyObject()";
}

void MyObject::doSomething() {
    qInfo() << "doing something";
}

void MyObject::dumpMe() {
    qInfo() << "dumping myobject " << this->objectName();
}

void MyObject::dumpMeWithArgument(const QString &arg) {
    qInfo() << "dumping myobject " << this->objectName() << " arg: " << arg;
}
