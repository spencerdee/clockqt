#include "alarmpage.h"
#include "ui_alarmpage.h"


ClockPage::ClockPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::ClockPage), count("")
{
    ui->setupUi(this);
    
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ClockPage::updateCount);
    timer->start(1000);

    connect(ui->alarm, &QPushButton::clicked, this, &ClockPage::alarmPressed);
    connect(ui->menu, &QPushButton::clicked, this, &ClockPage::menuPressed);
}

ClockPage::~ClockPage()
{
    delete ui;
}

void ClockPage::alarmPressed() {
    ui->count->setText("ALARM");
}

void ClockPage::menuPressed() {
    ui->count->setText("MENU");
}

void ClockPage::updateCount() {
    auto t = std::chrono::system_clock::now();
    std::time_t now = std::time(0);
    tm *ltm = localtime(&now);

    std::stringstream b;
    b << std::put_time(ltm, "%a %b %d %H:%M:%S %Y");

    count = QString::fromStdString(b.str());
    ui->count->setText(count);
    update();
}