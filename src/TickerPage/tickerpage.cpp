#include "tickerpage.h"
#include <QDebug>
#include <QPainter>
#include <qcolor.h>
#include <string>
#include <fstream>

TickerPage::TickerPage(QWidget *parent, QString text) :
    QWidget(parent), scrollPos(0)
{
    tickerFields = QMap<QString, QString>();
    timer = new QTimer();
    staticText.setTextFormat(Qt::PlainText);
    setFixedHeight(fontMetrics().height());
    leftMargin = width();
    setSeparator(" ");
    connect(timer, &QTimer::timeout, this, &TickerPage::timeout);
    timer->setInterval(100);
    timer->start();
    setText(text);

    std::ifstream file("api-keys.csv");
    if (!file.is_open()) {
        qDebug() << "Could not open file: " << QString::fromStdString("apiFile.csv");
    }
    else
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::string key = line.substr(0, line.find(","));
            std::string value = line.substr(line.find(",") + 1);
            if (key == "weather")
            {
                weatherApiKey = value;
                qDebug() << "Weather API Key: " << QString::fromStdString(weatherApiKey);
            }
        }
    }
    file.close();
    // TODO: read in weather api key and implement api calls to show weather in ticker
}

TickerPage::~TickerPage() {

};

QString TickerPage::text() const
{
    return _text;
}

void TickerPage::setText(QString text)
{
    _text = text;
    updateText();
    update();
}

void TickerPage::setField(QString key, QString val) {
    tickerFields[key] = val;
}

QString TickerPage::separator() const
{
    return _separator;
}

void TickerPage::setSeparator(QString separator)
{
    _separator = separator;
    updateText();
    update();
}

void TickerPage::updateText()
{
    timer->stop();
    staticText.setText(_text + _separator);
    staticText.prepare(QTransform(), font());
    wholeTextSize = QSize(fontMetrics().horizontalAdvance(staticText.text()), fontMetrics().height());
    timer->start();
}

void TickerPage::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    int windowWidth = width();
    int i = scrollPos;
    while(i < windowWidth + wholeTextSize.width()) {
        buffer = QImage(size(), QImage::Format_ARGB32_Premultiplied);

        buffer.fill(qRgba(0, 0 ,0, 0));
        QPainter pb(&buffer);
        pb.setPen(painter.pen());
        pb.setPen(Qt::white);
        pb.setFont(painter.font());

        int x = qMin(-i, 0) + windowWidth;

        if(x < windowWidth)
        {
            pb.setBrush(QColor(0, 0, 0, 0.4 * 255));
            QRect rect(QPoint(x, (height() - wholeTextSize.height()) / 2) + QPoint(0,0), wholeTextSize);
            pb.drawRect(rect);
            pb.drawStaticText(QPointF(x, (height() - wholeTextSize.height()) / 2) + QPoint(0,0), staticText);
            x += wholeTextSize.width();

            painter.drawImage(0, 0, buffer);
        } 
        i += wholeTextSize.width();
    }
    if (scrollPos > wholeTextSize.width()) {
        scrollPos = 0;
    }
}

void TickerPage::timeout()
{
    scrollPos = (scrollPos + 1);
    QString toTicker = "";
    for (QString key : tickerFields.keys()) {
        if (tickerFields[key] != "") {
            toTicker += tickerFields[key] + " | ";
        }
    }
    setText(toTicker);
    update();
    // setText(QString("Scroll Pos = %1 | Width = %2").arg(scrollPos).arg(width()));
}