#include "electionresult.h"

ElectionResult::ElectionResult()
{

}

double ElectionResult::index(int index) {
    switch(index) {
    case 0: return cducsu;
    case 1: return spd;
    case 2: return green;
    case 3: return fdp;
    case 4: return afd;
    case 5: return left;
    case 6: return misc;
    }
    return 0;
}


static double getGermanDouble(const QString &s) {
    QString c = s;
    c.replace(",", ".");
    return c.toDouble();
}


ElectionResult ElectionResult::fromJsonArray(QJsonArray array) {
    ElectionResult r;
    r.area = array.at(0).toString();
    r.year = array.at(1).toInt();

    //CDU/CSU;SPD;GRÜNE;FDP;AfD;DIE LINKE;Sonstige
    int ptr = 10;
    r.cducsu = getGermanDouble(array.at(ptr++).toString());
    r.spd = getGermanDouble(array.at(ptr++).toString());
    r.green = getGermanDouble(array.at(ptr++).toString());
    r.fdp = getGermanDouble(array.at(ptr++).toString());
    r.afd = getGermanDouble(array.at(ptr++).toString());
    r.left = getGermanDouble(array.at(ptr++).toString());
    r.misc = getGermanDouble(array.at(ptr++).toString());

    return r;
}

