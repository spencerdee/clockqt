#include "clockpage.h"
#include <iostream>

ClockPage::ClockPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::ClockPage), time(""), date("")
{
    ui->setupUi(this);
    
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ClockPage::updateTime);
    timer->start(1000);
    clockOn = true;
}

ClockPage::~ClockPage()
{
    delete ui;
}

Ui::ClockPage* ClockPage::getUi()
{
    return ui;
}

void ClockPage::updateFont() {
    ui->time->setText("");
    // ui->date->setText("");
    // font = QFont("Ariel", int(this->width() / 30), QFont::Bold);
    // ui->date->setFont(font);
    font = QFont("Ariel", int(this->width() / 20), QFont::Bold);
    ui->time->setFont(font);
}

void ClockPage::setInterval(int ms) {
    timer->stop();
    timer->start(ms);
}

void ClockPage::updateTime() {
    // sets timer to every 10 sec when not open
    if (!isVisible()) {
        setInterval(10000);
    } else {
        setInterval(100);
    }

    if (clockOn) {
        // grab system time
        tm tm{};
        getCurrentTime(&tm);

        std::stringstream bTime;
        bTime << std::put_time(&tm, "%H:%M:%S %p");
        time = QString::fromStdString(bTime.str());
        ui->time->setText(QString("%1").arg(time));

        // std::stringstream bDate;
        // bDate << std::put_time(&tm, "%a %b %d %Y");
        // date = QString::fromStdString(bDate.str());
        // ui->date->setText(QString("%1").arg(date));
    }

    update();
    //clockOn = false;
}