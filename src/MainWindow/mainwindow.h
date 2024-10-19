#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clockpage.h"
#include "menupage.h"
#include "tickerpage.h"
#include "alarmpage.h"
#include "menupage.h"
#include "backgroundpage.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setView(QWidget* w);

public slots:
    void alarmPressed();
    void clockPressed();
    void menuPressed();
    void backgroundPressed();
    void addToTicker(QString key, QString val);
    void setBackground(QString path);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;
    ClockPage* cp;
    AlarmPage* ap;
    TickerPage* tp;
    MenuPage* mp;
    BackgroundPage* bp;
    QWidget* currentView;
    QString backgroundPath;
    void setupConnections();
};
#endif // MAINWINDOW_H
