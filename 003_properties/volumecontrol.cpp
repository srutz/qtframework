#include "volumecontrol.h"

VolumeControl::VolumeControl(QObject *parent)
    : QObject{parent}, m_volume(25)
{
}

double VolumeControl::volume() const
{
    return m_volume;
}

void VolumeControl::setVolume(double volume)
{
    if (m_volume == volume) {
        return;
    }
    m_volume = volume;
    emit volumeChanged(m_volume);
}

