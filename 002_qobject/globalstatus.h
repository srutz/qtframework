#ifndef GLOBALSTATUS_H
#define GLOBALSTATUS_H

#include <QObject>

class GlobalStatus : public QObject
{
    Q_OBJECT
    QString statusKey_;
    inline static GlobalStatus* instance = nullptr;

public:
    explicit GlobalStatus(QObject *parent = nullptr);
    ~GlobalStatus();

    static GlobalStatus* getInstance();

    const QString& statusKey() const;
    void setStatusKey(const QString& statusKey);

signals:

    void statusKeyChanged();
    void statusKeyChangedWithStatusKey(const QString &statusKey);



};

#endif // GLOBALSTATUS_H
