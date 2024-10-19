#include "menupage.h"
#include <iostream>

MenuPage::MenuPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::MenuPage)
{
    ui->setupUi(this);
    
}

MenuPage::~MenuPage()
{
    delete ui;
}

Ui::MenuPage* MenuPage::getUi()
{
    return ui;
}