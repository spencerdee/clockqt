#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ClockPage* cp = new ClockPage;
    ui->centralwidget->layout()->replaceWidget(ui->CenterWindow, cp);

    TickerPage* tp = new TickerPage;
    tp->setText("TICKER 1 TICKER 2 TICKER 3 TICKER 1 TICKER 2 TICKER 3 TICKER 1 TICKER 2 TICKER 3 TICKER 1 TICKER 2 TICKER 3 TICKER 1 TICKER 2 TICKER 3 TICKER 1 TICKER 2 TICKER 3");
    ui->centralwidget->layout()->replaceWidget(ui->BottomBar, tp);
}

MainWindow::~MainWindow()
{
    delete ui;
}