#include "alarmpage.h"
#include "tickerpage.h"

AlarmPage::AlarmPage(TickerPage* tp, QWidget *parent)
    : QWidget(parent), ui(new Ui::AlarmPage), alarmOn(false), alarmActivated(false), tp(tp)
{
    ui->setupUi(this);

    setAlarmTime(0);
    alarmCheckTimer = new QTimer(this);
    connect(alarmCheckTimer, &QTimer::timeout, this, &AlarmPage::checkAlarm);
    alarmCheckTimer->start(60000);

    pushButtonTimer = new QTimer(this);
    pushButtonTimer->start(10);
    connect(pushButtonTimer, &QTimer::timeout, this, &AlarmPage::pushButtonCheck);
    connect(ui->plus, &QPushButton::clicked, this, &AlarmPage::plus);
    connect(ui->minus, &QPushButton::clicked, this, &AlarmPage::minus);
    connect(ui->minus, &QPushButton::released, this, [this](){minusDown = 0;});
    connect(ui->plus, &QPushButton::released, this, [this](){plusDown = 0;});
    connect(ui->alarmOff, &QPushButton::clicked, this, &AlarmPage::alarmOff);

    updateFont();
}

AlarmPage::~AlarmPage()
{
    delete ui;
}

Ui::AlarmPage* AlarmPage::getUi()
{
    return ui;
}

void AlarmPage::updateFont() {
    QFont font = QFont("Ariel", int(this->width() / 40), QFont::Bold);
    ui->alarmTime->setFont(font);
}

QString AlarmPage::alarmTimeToString(int alarmTime)
{
    if (alarmTime < 0) {
        alarmTime += 1440;
    } else if (alarmTime >= 1440) {
        alarmTime -= 1440;
    }
    int hour = alarmTime / 60;
    if (hour > 12) {
        hour -= 12;
    } else if (hour == 0) {
        hour = 12;
    }
    this->alarmTime = alarmTime;
    return QString("%1:%2 %3")
        .arg(hour)
        .arg(alarmTime % 60, 2, 10, QLatin1Char('0'))
        .arg(alarmTime > 720 ? "pm" : "am");
}

void AlarmPage::checkAlarm() {
    tm tm = {};
    getCurrentTime(&tm);

    if (alarmTime == tm.tm_hour * 60 + tm.tm_min && alarmOn) {
        alarmActivated = true;
        emit alarmTriggered();
        ui->alarmOff->setText("SILENCE ALARM");
    }
}

void AlarmPage::alarmOff() {
    if (alarmActivated) {
        alarmActivated = false;
    } else {
        alarmOn = !alarmOn;
    }
    if (alarmOn) {
        ui->alarmOff->setText("ALARM IS ON");
    } else {
        ui->alarmOff->setText("ALARM IS OFF");
    }
    QString a = QString("Alarm");
    QString b = QString("Alarm is " + QString(alarmOn ? "ON" : "OFF") + " and set to " + alarmTimeToString(alarmTime));
    tp->setField(a, b);
    //tp->setField(QString("Alarm"), QString("Alarm is " + QString(alarmOn ? "ON" : "OFF") + " and set to " + alarmTimeToString(alarmTime)));
}

void AlarmPage::plus() {
    setAlarmTime(alarmTime + 5);
    tp->setField(QString("Alarm"), QString("Alarm is " + QString(alarmOn ? "ON" : "OFF") + " and set to " + alarmTimeToString(alarmTime)));
}

void AlarmPage::minus() {
    setAlarmTime(alarmTime - 5);
    tp->setField(QString("Alarm"), QString("Alarm is " + QString(alarmOn ? "ON" : "OFF") + " and set to " + alarmTimeToString(alarmTime)));
}

void AlarmPage::setAlarmTime(int alarmTime) {
    ui->alarmTime->setText(alarmTimeToString(alarmTime));
}

void AlarmPage::pushButtonCheck() {
    if (ui->minus->isDown()) {
        if (minusDown > 100) {
            minus();
        } else {
            minusDown++;
        }
    } else {
        minusDown = 0;
    }

    if (ui->plus->isDown()) {
        if (plusDown > 50) {
            plus();
        } else {
            plusDown++;
        }
    } else {
        plusDown = 0;
    }
    updateFont();
}

bool AlarmPage::getAlarmStatus() {
    return alarmOn;
}

QString AlarmPage::getAlarmTime()
{
    return ui->alarmTime->text();
}
