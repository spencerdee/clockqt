#ifndef CLOCKPAGE_H
#define CLOCKPAGE_H

#include <QWidget>
#include <QTimer>
#include <ctime>
#include <iomanip>
#include <iostream>

namespace Ui {
class ClockPage;
}

class ClockPage : public QWidget
{
    Q_OBJECT

public:
    ClockPage(QWidget *parent = nullptr);
    virtual ~ClockPage();

private slots:
    void updateCount();
    void alarmPressed();
    void menuPressed();

private:
    Ui::ClockPage *ui;
    QTimer* timer;
    QString count;
};
#endif // CLOCKPAGE_H
