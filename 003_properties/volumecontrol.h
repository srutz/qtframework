#ifndef VOLUMECONTROL_H
#define VOLUMECONTROL_H

#include <QObject>
#include <QDebug>
#include <iostream>

class VolumeControl : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double volume READ volume WRITE setVolume NOTIFY volumeChanged)
public:
    explicit VolumeControl(QObject *parent = nullptr);

    double volume() const;
    void setVolume(double);
signals:
    void volumeChanged(double);

private:
    double m_volume;
};


inline QDebug operator<< (QDebug s, const VolumeControl &v)
{
    s.nospace() << "VolumeControl { volume=" << v.volume() << " }";
    return s;
}

inline std::ostream & operator<<(std::ostream &os, const VolumeControl &v)
{
    os << "VolumnControl ... { volumne=" << v.volume() << "}";
    return os;
}


#endif // VOLUMECONTROL_H
