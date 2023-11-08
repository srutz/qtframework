#ifndef GUIWORKER_H
#define GUIWORKER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include "winmain.h"

class GuiWorker : public QObject
{
    Q_OBJECT
public:
    explicit GuiWorker(QObject *parent = nullptr): QObject(parent)
    {
    }

public slots:
    void process()
    {
        qInfo() << "thread start";
        /* thread body */
        launchWindows();
        qInfo() << "thread done";
        emit finished();
    }

signals:
    void finished();

};

#endif // GUIWORKER_H
