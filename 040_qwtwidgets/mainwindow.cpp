#include <QDebug>
#include <QwtDialNeedle>
#include <QFile>

#include <QwtPlot>
#include <QwtPlotCurve>
#include <QwtPlotGrid>
#include <QwtSymbol>
#include <QwtLegend>

#include <QPropertyAnimation>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_aboutdialog.h"

class AboutDialog : public QDialog, private Ui::AboutDialog {
public:
    AboutDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setupUi(this);
        qInfo() << "dialog";
    }
};

class MyKnob : public QwtKnob {
public:

    MyKnob(QWidget *parent = nullptr) : QwtKnob(parent) {
        counter = 0;
    }

    void mousePressEvent( QMouseEvent* ) override
    {
        setValueAnimated(counter% 2 == 0 ? this->maximum() : this->minimum());
        counter++;
    }

    void setValueAnimated(double value)
    {
        auto animation = new QPropertyAnimation(this, "value", this);
        animation->setDuration(750);
        animation->setStartValue(this->value());
        animation->setEndValue(value);
        animation->setEasingCurve(QEasingCurve::InOutQuad);
        animation->setEasingCurve(QEasingCurve::InOutElastic);
        animation->start();
        connect(animation, &QPropertyAnimation::finished, this, [=]() {
            delete animation;
        });
    }

private:
    int counter;
};


struct Entry {
    EntryId id;
    QString title;
};

static Entry entries[] = {
    { ID_KNOB, "Qwt Knob" },
    { ID_SLIDER, "Qwt Slider" },
    { ID_DIAL, "Qwt Dial" },
    { ID_PLOT, "Qwt Plot" },
    };

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->splitter->setSizes({ 500, 1000});

    //ui->container->setPalette(Qt::darkGray);

    for (auto entry : entries) {
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        item->setText(entry.title);
        item->setData(1, QVariant(entry.id));
        ui->listWidget->addItem(item);
        QObject::connect(ui->listWidget, &QListWidget::itemClicked, this, [=] (QListWidgetItem *item) {
            this->showEntry(static_cast<EntryId>(item->data(1).toInt()));
        });
    }

    showEntry(ID_KNOB);

    // about dialog
    QObject::connect(ui->actionAbout, &QAction::triggered, this, [=]() {
        AboutDialog dialog(this);
        dialog.setModal(true);
        dialog.show();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


QWidget* MainWindow::makeDial()
{
    int n = 4;
    int n_2 = std::sqrt(n);
    QWidget *panel = new QWidget(this);
    auto layout = new QGridLayout(panel);
    layout->setSpacing(8);
    panel->setLayout(layout);
    //panel->setStyleSheet("background-color: #dddddd;");
    for (int i = 0; i < n; i++) {
        int row = i / n_2;
        int column = i % n_2;
        auto dial = new QwtDial();
        dial->setTracking(true);
        dial->setFocusPolicy(Qt::StrongFocus);
        dial->setObjectName("dial1");
        dial->setOrigin(135.0);
        dial->setScaleArc(0.0, 270.0);
        dial->setScaleMaxMinor(4);
        dial->setScaleMaxMajor(10);
        dial->setScale(-100.0, 100.0);
        dial->setValue(75);

        QColor needleColor(Qt::red);
        needleColor = QColor("Goldenrod");
        QwtDialSimpleNeedle* needle = new QwtDialSimpleNeedle(
            QwtDialSimpleNeedle::Arrow, true, needleColor,
            QColor(Qt::gray).lighter(130));
        dial->setNeedle(needle);

        const QColor base( QColor(Qt::darkGray).darker(150));

        QPalette palette;
        palette.setColor(QPalette::Base, base);
        palette.setColor(QPalette::Window, base.darker(150));
        palette.setColor(QPalette::Mid, base.darker(110));
        palette.setColor(QPalette::Light, base.lighter(170));
        palette.setColor(QPalette::Dark, base.darker(170));
        palette.setColor(QPalette::Text, base.darker(200).lighter(800));
        palette.setColor(QPalette::WindowText, base.darker(200));

        dial->setPalette(palette);
        dial->setLineWidth(4);
        dial->setFrameShadow(QwtDial::Sunken);
        layout->addWidget(dial, row, column);
    }
    return panel;
}


QWidget* MainWindow::makeSlider()
{
    return 0;
}

QWidget* MainWindow::makeKnob()
{
    int n = 9;
    int n_2 = std::sqrt(n);
    QWidget *panel = new QWidget(this);
    auto layout = new QGridLayout(panel);
    layout->setSpacing(8);
    panel->setLayout(layout);
    panel->setStyleSheet("background-color: #dddddd;");
    for (int i = 0; i < n; i++) {
        int row = i / n_2;
        int column = i % n_2;
        auto knob = new MyKnob();
        knob->setTracking(true);
        knob->setKnobStyle(row == 0 ? QwtKnob::Raised : row == 1 ? QwtKnob::Sunken : QwtKnob::Flat);
        knob->setMarkerStyle(QwtKnob::Dot);
        knob->setWrapping(false);
        layout->addWidget(knob, row, column);
    }
    return panel;
}

QWidget* MainWindow::makePlot()
{
    auto plot = new QwtPlot();
    //plot->setTitle("Plot Demo");
    plot->setCanvasBackground(Qt::white);
    plot->setAxisScale(QwtAxis::XBottom, -10.0, 10.0);
    plot->setAxisScale(QwtAxis::YLeft, -10.0, 10.0);
    plot->insertLegend(new QwtLegend());

    QwtPlotGrid* grid = new QwtPlotGrid();
    grid->attach(plot);

    {
        QwtPlotCurve* curve = new QwtPlotCurve();
        curve->setTitle("f(x) = 5 * sin(x)");
        curve->setPen(QColor("green"), 1.5), curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
        QPolygonF points;
        int steps = 50;
        double x = -10;
        for (int i = 0; i < steps; i++) {
            double y = 5 * std::sin(x);
            x += 20.0 / steps;
            points << QPointF(x, y);
        }
        curve->setSamples(points);
        curve->attach(plot);
    }

    {
        QwtPlotCurve* curve = new QwtPlotCurve();
        curve->setTitle("f(x) = 4 / x");
        curve->setPen(QColor("orange"), 1.5), curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
        QPolygonF points;
        int steps = 50;
        double x = -10;
        for (int i = 0; i < steps; i++) {
            double y = 4 / x;
            x += 20.0 / steps;
            points << QPointF(x, y);
        }
        curve->setSamples(points);
        curve->attach(plot);
    }
    return plot;
}


void MainWindow::showEntry(EntryId id)
{
    qInfo() << "showing " << id;

    QString title;
    switch (id) {
    case ID_KNOB:
        title = "Qwt Knob"; break;
    case ID_SLIDER:
        title = "Qwt Slider"; break;
    case ID_PLOT:
        title = "Qwt Plot"; break;
    }
    ui->title->setText(title);

    while (ui->container->children().size() > 0) {
        auto * child = ui->container->children().at(0);
        delete child;
    }

    switch (id) {
    case ID_KNOB:
        showWidget(makeKnob());
        break;
    case ID_SLIDER:
        break;
    case ID_DIAL:
        showWidget(makeDial());
        break;
    case ID_PLOT:
        showWidget(makePlot());
        break;
    }
}

void MainWindow::showWidget(QWidget *widget)
{
    auto layout = new QVBoxLayout(ui->container);
    layout->addWidget(widget);
    ui->container->setLayout(layout);
}

