#include "backgroundpage.h"
#include <filesystem>
#include <qnamespace.h>
#include <qobject.h>
#include <qgroupbox.h>
#include <QSizePolicy>
#include <qsizepolicy.h>
#include <qdir.h>

BackgroundPage::BackgroundPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::BackgroundPage)
{
    ui->setupUi(this);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QScroller::grabGesture(ui->scrollArea, QScroller::LeftMouseButtonGesture);

    QGroupBox* gb = new QGroupBox();
    vbl = new QVBoxLayout;

    buttons = QList<QPushButton*>();

    QDir dir("images");

    for (const auto & entry : dir.entryInfoList(QDir::Files)) {
        QPushButton* button = new QPushButton();
        button->setFixedHeight(50);
        button->setText(entry.fileName());
        button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        vbl->addWidget(button);
        buttons.append(button);
    }

    // for (const auto & entry : std::filesystem::directory_iterator("images")) {
    //     QPushButton* button = new QPushButton();
    //     button->setFixedHeight(50);
    //     button->setText(QString::fromStdString(entry.path().filename().string()));
    //     button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    //     vbl->addWidget(button);
    //     buttons.append(button);
    // }
    gb->setLayout(vbl);
    ui->scrollArea->setWidget(gb);
}

BackgroundPage::~BackgroundPage()
{
    delete ui;
}

Ui::BackgroundPage* BackgroundPage::getUi()
{
    return ui;
}

QList<QPushButton*> BackgroundPage::getButtons() {
    return buttons;
}