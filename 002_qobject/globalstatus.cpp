#include <QDebug>
#include "globalstatus.h"

GlobalStatus* GlobalStatus::getInstance()
{
    if (!instance) {
        instance = new GlobalStatus();
    }
    return instance;
}

GlobalStatus::GlobalStatus(QObject *parent)
    : QObject{parent}, statusKey_("status.none")
{
    qInfo() << "GlobalStatus created";
}

GlobalStatus::~GlobalStatus()
{
    qInfo() << "GlobalStatus destroyed";
}

const QString& GlobalStatus::statusKey() const
{
    return this->statusKey_;
}

void GlobalStatus::setStatusKey(const QString& statusKey)
{
    if (this->statusKey_ == statusKey) {
        return; // no change
    }
    this->statusKey_ = statusKey;
    emit statusKeyChanged();
    emit statusKeyChangedWithStatusKey(this->statusKey_);
}

