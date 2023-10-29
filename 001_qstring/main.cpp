#include <QDebug>
#include <QCoreApplication>
#include <QByteArray>
#include <QRegularExpression>
#include <QString>
#include <QFile>
#include <QTime>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    {
        QRegularExpression regex = QRegularExpression("\\s+");
        QString s = "one two three\tfound  ";
        auto words = s.split(regex, Qt::SkipEmptyParts);
        for (const QString& word : words) {
            qInfo() << word;
        }
    }


#ifdef ZERO1
    {
        QString bible = "";
        QFile f("/home/sr/work/qt/objecttest/bible.txt");
        if(f.open(QIODevice::ReadOnly)) {
            QByteArray data = f.readAll();
            bible = QString::fromUtf8(data);
        }
        auto lines = bible.split("\n");
        QSet<QString> words;
        QRegularExpression regex = QRegularExpression("\\s+");
        int wordCount = 0;
        for (auto &line : lines) {
            auto linewords = line.split(regex, Qt::SkipEmptyParts);
            for (auto const &word : linewords) {
                words.insert(word.trimmed());
                ++wordCount;
            }
        }
        qInfo() << "linecount: " << lines.size();
        qInfo() << "words: " << wordCount;
        qInfo() << "distinct words: " << words.size();
    }
#endif


#ifdef ZERO2
    {
        QString bible = "";
        QFile f("/home/sr/work/qt/objecttest/bible.txt");
        QTime t0;
        t0 = QTime::currentTime();
        if(f.open(QIODevice::ReadOnly)) {
            QByteArray data = f.readAll();
            bible = QString::fromUtf8(data);
        }
        qInfo() << "read took: " << t0.msecsTo(QTime::currentTime());

        t0 = QTime::currentTime();
        auto lines = bible.split("\n");
        qInfo() << "line split took: " << t0.msecsTo(QTime::currentTime());
        t0 = QTime::currentTime();
        QSet<QString> words;
        QRegularExpression regex = QRegularExpression("\\s+");
        int wordCount = 0;
        for (auto &line : lines) {
            auto linewords = line.split(regex, Qt::SkipEmptyParts);
            //auto linewords = line.split(" ", Qt::SkipEmptyParts);
            for (auto const &word : linewords) {
                words.insert(word.trimmed());
                ++wordCount;
            }
        }
        qInfo() << "processing took: " << t0.msecsTo(QTime::currentTime());
        qInfo() << "linecount: " << lines.size();
        qInfo() << "words: " << wordCount;
        qInfo() << "distinct words: " << words.size();
    }
#endif

    return a.exec();
}
