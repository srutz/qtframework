#include <QCoreApplication>
#include <QVariant>
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

#ifdef VARIANTS
    QVariant v1(100);
    QVariant v2(100.0);
    QVariant v3("100.0");

    qInfo() << "v1: " << v1 << " " << v1.typeId();
    qInfo() << "v1: " << v1 << " " << v1.metaType().id();
    qInfo() << "v1: " << v1 << " " << v1.metaType().name();

    qInfo() << "v2: " << v2 << " " << v2.metaType().name();
    qInfo() << "v3: " << v3 << " " << v3.metaType().name();
#endif


    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("template1");
    db.setUserName("sr");
    db.setPassword("abc");
    bool ok = db.open();
    qInfo() << "database connection status " << ok;

    QString sql = "select relname, relpages, reltuples cnt from pg_class where relname ilike ? order by relpages desc limit 5";
    {
        QSqlQuery query;
        query.prepare(sql);
        query.bindValue(0, QVariant("%\\_user\\_%"));
        if (query.exec()) {
            while (query.next()) {
                auto relnameV = query.value("relname");
                auto relpagesV = query.value("relpages");
                auto cntV = query.value("cnt");
                auto relname = relnameV.toString();
                auto relpages = relpagesV.toInt();
                auto cnt = cntV.toInt();
                qInfo().noquote().nospace() << "relname=" << relname << ", relpages=" << relpages << ", cnt=" << cnt;
            }
        } else {
            qDebug() << query.lastError().text();
        }
    }
    return 0;
}
