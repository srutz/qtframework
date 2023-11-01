#ifndef ELECTIONRESULT_H
#define ELECTIONRESULT_H

#include <QString>
#include <QJsonArray>

struct ElectionResult
{
    QString area;
    int year;

    double cducsu;
    double spd;
    double green;
    double fdp;
    double afd;
    double left;
    double misc;


    ElectionResult();
    double index(int);

    static ElectionResult fromJsonArray(QJsonArray array);
};

#endif // ELECTIONRESULT_H

