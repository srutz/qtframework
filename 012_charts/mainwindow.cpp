#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "util.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QBarSet>
#include <QBarSeries>
#include <QStringList>
#include <QChartView>
#include <QBarCategoryAxis>
#include <QValueAxis>

#include <QStringListModel>

#include "electionresult.h"

using namespace Qt::StringLiterals;

QStringList categories { "CDU/CSU", "SPD", "Grüne", "FDP", "Afd", "Die Linke", "Sonstige" };

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->splitter->setStretchFactor(0, 15);
    ui->splitter->setStretchFactor(1, 85);

    auto listModel = new QStringListModel(this);
    listModel->setStringList(QStringList {
        "Deutschland",
        "Baden-Württemberg",
        "Bayern",
        "Berlin",
        "Brandenburg",
        "Bremen",
        "Hamburg",
        "Hessen",
        "Mecklenburg-Vorpommern",
        "Niedersachsen",
        "Nordrhein-Westfalen",
        "Rheinland-Pfalz",
        "Saarland",
        "Sachsen",
        "Schleswig-Holstein",
        "Thüringen"
    });
    ui->listView->setModel(listModel);
    ui->listView->setEditTriggers(QListView::NoEditTriggers);
    connect(ui->listView, &QListView::clicked, this, [=](const QModelIndex &index) {
        auto item = listModel->data(index);
        auto area = item.toString();
        auto series = this->fillChart(area);
        series->setParent(chart);
        chart->removeAllSeries();
        chart->addSeries(series);
        this->chart->setTitle("Wahrergebnisse " + area);
        auto axes = chart->axes();
        series->attachAxis(axes[0]);
        series->attachAxis(axes[1]);
        qInfo() << "click: " << index << ": " << item;
    });

    this->chart = new QChart();
    chart->setTitle("Wahlergebnisse Deutschland");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    /* load json from file */
    auto json = Util::readResourceAsString(":/convertcsv.json");
    QJsonParseError error;
    auto document = QJsonDocument::fromJson(json.toUtf8(), &error);
    auto lines = document.array();
    auto results = QVector<ElectionResult>();
    for (const auto &line : lines) {
        if (line.isArray()) {
            auto lineArray = line.toArray();
            results.push_back(ElectionResult::fromJsonArray(lineArray));
        }
    }

    /* now we have an array (vector) of results */
    this->electionMap = new QMap<QString,ElectionResult>();
    for (const auto &result : results) {
        auto key = result.area + "/" + QString::number(result.year);
        electionMap->insert(key, result);
    }

    auto series = this->fillChart("Deutschland");
    series->setParent(chart);
    chart->removeAllSeries();
    chart->addSeries(series);

    auto axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);

    auto axisY = new QValueAxis();
    double max = 60;
    axisY->setRange(0, max);
    axisY->setTickCount(max / 10 + 1);
    axisY->setMinorTickCount(10);
    chart->addAxis(axisY, Qt::AlignLeft);
    auto axes = chart->axes();
    series->attachAxis(axes[0]);
    series->attachAxis(axes[1]);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    auto chartView = new QChartView(chart);
    QVBoxLayout *layout = new QVBoxLayout(ui->rightWidget);
    layout->addWidget(chartView);

    QObject::connect(series, &QAbstractBarSeries::clicked, series, [=](int index, QBarSet *set) {
        set->toggleSelection({index});
        QString category = categories[index];
        qInfo() << "selected " << category << ", set=" << set << ", index=" << index;
        auto results2021 = electionMap->value(m_area + "/2021");
        auto results2017 = electionMap->value(m_area + "/2017");

        double percent2021 = results2021.index(index);
        double percent2017 = results2017.index(index);

        QString info = QString::asprintf("%ls, 2021=%.2f%%, 2017=%.2f%%", category.utf16(), percent2021, percent2017);
        qInfo() << info;
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

QBarSeries* MainWindow::fillChart(const QString &area)
{
    this->m_area = area;
    auto y2021 = new QBarSet("2021");
    auto y2017 = new QBarSet("2017");

    auto results2021 = electionMap->value(area + "/2021");
    auto results2017 = electionMap->value(area + "/2017");

    *y2021 << results2021.cducsu
           << results2021.spd
           << results2021.green
           << results2021.fdp
           << results2021.afd
           << results2021.left
           << results2021.misc;
    *y2017 << results2017.cducsu
           << results2017.spd
           << results2017.green
           << results2017.fdp
           << results2017.afd
           << results2017.left
           << results2017.misc;


    QBarSeries *series = new QBarSeries();
    series->append(y2021);
    series->append(y2017);
    return series;
}

