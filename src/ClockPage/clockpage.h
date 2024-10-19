#ifndef CLOCKPAGE_H
#define CLOCKPAGE_H

#include <QWidget>
#include <QTimer>
#include <qfont.h>
#include <iomanip>
#include <sstream>
#include "common.h"
#include "ui_clockpage.h"


namespace Ui {
class ClockPage;
}

class ClockPage : public QWidget
{
    Q_OBJECT

public:
    ClockPage(QWidget *parent = nullptr);
    virtual ~ClockPage();
    Ui::ClockPage* getUi();
    void setInterval(int ms);
    void updateFont();

private slots:
    void updateTime();

private:
    Ui::ClockPage *ui;
    QTimer* timer;
    QString time;
    QString date;
    QFont font;
    bool clockOn;
};
#endif // CLOCKPAGE_H
