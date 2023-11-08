#ifndef GUIOWNER_H
#define GUIOWNER_H

#include <QObject>
#include <QDebug>
#include "guiworker.h"

class GuiOwner : public QObject
{
    Q_OBJECT
public:
    explicit GuiOwner(QObject *parent = nullptr) : QObject(parent)
    {
        worker = nullptr;
        thread = nullptr;
    }

    void launch()
    {
        if (worker) {
            qDebug() << "already running";
            return;
        }
        qDebug() << "launching";
        worker = new GuiWorker();
        thread = new QThread();
        worker->moveToThread(thread);
        connect(thread, &QThread::started, worker, &GuiWorker::process);
        connect(worker, &GuiWorker::finished, thread, &QThread::quit);
        thread->start();
    }

private:
    QThread *thread;
    GuiWorker *worker;

};

#endif // GUIOWNER_H
