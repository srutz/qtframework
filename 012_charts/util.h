#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QStringConverter>
#include <QByteArray>

class Util
{
public:
    Util();

    static QString readResourceAsString(const QString &path, QStringConverter::Encoding encoding = QStringConverter::Utf8);
    QByteArray readResourceAsBytes(const QString &path);

};

#endif // UTIL_H
