#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QStringConverter>

class Util
{
public:
    Util();

    static QString readResourceAsString(const QString &path, QStringConverter::Encoding encoding = QStringConverter::Utf8);

};

#endif // UTIL_H
