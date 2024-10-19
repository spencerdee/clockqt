#ifndef BACKGROUNDPAGE_H
#define BACKGROUNDPAGE_H

#include <QWidget>
#include <QTimer>
#include <qfont.h>
#include "common.h"
#include <filesystem>
#include <stdlib.h>
#include <QList>
#include <QScroller>
#include "ui_backgroundpage.h"

namespace Ui {
class BackgroundPage;
}

class BackgroundPage : public QWidget
{
    Q_OBJECT

public:
    BackgroundPage(QWidget *parent = nullptr);
    virtual ~BackgroundPage();
    Ui::BackgroundPage* getUi();
    QList<QPushButton*> getButtons();

signals:
    void setBackground(QString path);

private:
    Ui::BackgroundPage *ui;
    QList<QPushButton*> buttons;
    QVBoxLayout* vbl;
};
#endif // BACKGROUNDPAGE_H
