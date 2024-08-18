#ifndef ALARMPAGE_H
#define ALARMPAGE_H

#include <QWidget>
#include <QTimer>
#include <ctime>
#include <iomanip>
#include <iostream>

namespace Ui {
class AlarmPage;
}

class AlarmPage : public QWidget
{
    Q_OBJECT

public:
    AlarmPage(QWidget *parent = nullptr);
    virtual ~AlarmPage();

private slots:
    void updateCount();
    void exitPressed();
    void menuPressed();

private:
    Ui::AlarmPage *ui;
    QTimer* timer;
    QString count;
};
#endif // CLOCKPAGE_H
