#include <QCoreApplication>
#include <QVariant>
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

/*

create table users (id bigserial, email text, name text);
insert into users(email,name) values ('harald.juhnke@de.de', 'Harald Juhnke');
insert into users(email,name) values ('frank.sinatra@de.de', 'Frank Sinatra'),('dean.martin@usa.com', 'Dean Martin');
insert into users(email,name) values ('hans.meiser@de.de', 'Hans Meiser');

*/

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
    db.setDatabaseName("db1");
    db.setUserName("sr");
    db.setPassword("abc");
    bool ok = db.open();
    qInfo() << "database connection status " << ok;

    {
        QString sql =
        "insert into users(email,name) values (:email, :name)";
        QSqlQuery query;
        query.prepare(sql);
        query.bindValue(":email", "willi.millowitsch@cologne.de");
        query.bindValue(":name", "Willi Millowitsch");
        if (query.exec()) {
            qInfo().nospace() << "inserted #" << query.numRowsAffected() << " row(s)";
        } else {
            qDebug() << query.lastError().text();
        }
    }

    {
        QString sql =
        "select email, name from users where email ilike ?";
        QSqlQuery query;
        query.prepare(sql);
        query.bindValue(0, QVariant("%ha%"));
        if (query.exec()) {
            while (query.next()) {
                auto email = query.value("email").toString();
                auto name = query.value("name").toString();
                qInfo().nospace().noquote() << "email=" << email << ", name=" << name;
            }
        } else {
            qDebug() << query.lastError().text();
        }
    }


    return 0;
}
