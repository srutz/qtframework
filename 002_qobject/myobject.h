#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>
#include <QDebug>

class MyObject : public QObject
{
    Q_OBJECT
public:
    explicit MyObject(QObject *parent = nullptr);
    ~MyObject();
    void doSomething();

public slots:
    void dumpMe();
    void dumpMeWithArgument(const QString &arg);

};

#endif // MYOBJECT_H
