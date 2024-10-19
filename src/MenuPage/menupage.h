#ifndef MENUPAGE_H
#define MENUPAGE_H

#include <QWidget>
#include <QTimer>
#include <qfont.h>
#include "common.h"
#include "ui_menupage.h"


namespace Ui {
class MenuPage;
}

class MenuPage : public QWidget
{
    Q_OBJECT

public:
    MenuPage(QWidget *parent = nullptr);
    virtual ~MenuPage();
    Ui::MenuPage* getUi();

private:
    Ui::MenuPage *ui;
};
#endif // MENUPAGE_H
