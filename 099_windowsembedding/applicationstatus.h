#ifndef APPLICATIONSTATUS_H
#define APPLICATIONSTATUS_H

#include <QObject>

enum ApplicationEvent {
    WIN_WM_CREATED = 1
};


class ApplicationStatus : public QObject
{
    Q_OBJECT

private:
    explicit ApplicationStatus(QObject *parent = nullptr)
        : QObject(parent) {
    }

public:
    static void initialize() {
        instance = new ApplicationStatus();
    }

    static ApplicationStatus* getInstance() {
        return instance;
    }


signals:
    void eventOccured(ApplicationEvent);


private:
    static ApplicationStatus *instance;

};

#endif // APPLICATIONSTATUS_H
