#include "mainwindow.h"
#include <qpushbutton.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    backgroundPath = "";

    // setWindowState(Qt::WindowMaximized);
    // setFixedSize(size());

    cp = new ClockPage;
    mp = new MenuPage;
    bp = new BackgroundPage;
    tp = new TickerPage;
    ap = new AlarmPage(tp);
    // may need to make pointers shared to avoid reference issues with init order

    ui->centralwidget->layout()->addWidget(mp);
    currentView = mp;
    ui->centralwidget->layout()->addWidget(tp);

    connect(cp->getUi()->alarm, &QPushButton::clicked, this, &MainWindow::alarmPressed);
    connect(cp->getUi()->menu, &QPushButton::clicked, this, &MainWindow::menuPressed);

    connect(ap, &AlarmPage::alarmTriggered, this, &MainWindow::alarmPressed);
    connect(ap->getUi()->clock, &QPushButton::clicked, this, &MainWindow::clockPressed);
    connect(ap->getUi()->menu, &QPushButton::clicked, this, &MainWindow::menuPressed);

    connect(mp->getUi()->alarm, &QPushButton::clicked, this, &MainWindow::alarmPressed);
    connect(mp->getUi()->clock, &QPushButton::clicked, this, &MainWindow::clockPressed);
    connect(mp->getUi()->background, &QPushButton::clicked, this, &MainWindow::backgroundPressed);
    connect(mp->getUi()->quit, &QPushButton::clicked, this, [this](){close();});

    connect(bp->getUi()->menu, &QPushButton::clicked, this, &MainWindow::menuPressed);
    connect(bp->getUi()->clock, &QPushButton::clicked, this, &MainWindow::clockPressed);

    for (QPushButton* button : bp->getButtons()) {
        connect(button, &QPushButton::clicked, this, [this, button](){setBackground(QString("images/" + button->text()));});
    }
    addToTicker("Alarm", QString("Alarm is " + QString(ap->getAlarmStatus() ? "ON" : "OFF") + " and set to " + ap->getAlarmTime()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setView(QWidget* w) {
    ui->centralwidget->layout()->replaceWidget(currentView, w);
    currentView->hide();
    currentView = w;
    w->show();
}

void MainWindow::setBackground(QString path) {
    backgroundPath = path;
    if (backgroundPath != "") {
        QPixmap bkgnd(path);
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
        addToTicker("Background", QString("Current Background: " + path.split("/")[1]));
    }
}

void MainWindow::clockPressed() {
    cp->updateFont();
    setView(cp);
    cp->setInterval(1000);
}

void MainWindow::menuPressed() {
    setView(mp);
}

void MainWindow::backgroundPressed() {
    setView(bp);
}

void MainWindow::addToTicker(QString key, QString val) {
    tp->setField(key, val);
}

void MainWindow::alarmPressed() {
    setView(ap);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   cp->updateFont();
   setBackground(backgroundPath);
}
