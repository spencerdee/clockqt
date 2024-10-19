#ifndef ALARMPAGE_H
#define ALARMPAGE_H

#include <QWidget>
#include <QTimer>
#include "common.h"
#include <iostream>
#include "ui_alarmpage.h"
#include <tickerpage.h>

namespace Ui {
class AlarmPage;
}

class AlarmPage : public QWidget
{
    Q_OBJECT

public:
    AlarmPage(TickerPage* tp, QWidget *parent = nullptr);
    virtual ~AlarmPage();
    Ui::AlarmPage* getUi();
    bool getAlarmStatus();
    QString getAlarmTime();

signals:
    void alarmTriggered();

private slots:
    void plus();
    void minus();
    void setAlarmTime(int alarmTime);
    void pushButtonCheck();
    void checkAlarm();
    void alarmOff();

private:
    Ui::AlarmPage *ui;
    QTimer* alarmCheckTimer;
    QTimer* pushButtonTimer;
    TickerPage* tp;
    void updateFont();
    QString alarmTimeToString(int alarmTime);
    bool alarmOn;
    bool alarmActivated;
    int alarmTime;
    int minusDown;
    int plusDown;
};
#endif // CLOCKPAGE_H
