#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <QDebug>

#include "util.h"

Util::Util()
{

}

QString Util::readResourceAsString(const QString &path, QStringConverter::Encoding encoding)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open embedded file.";
        return QString();
    }

    QTextStream stream(&file);
    stream.setEncoding(encoding);
    QString data= stream.readAll();
    file.close();
    return data;
}

QByteArray Util::readResourceAsBytes(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open embedded file.";
        return QByteArray();
    }
    QByteArray data = file.readAll();
    file.close();
    return data;
}


