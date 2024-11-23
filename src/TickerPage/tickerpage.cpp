#include "tickerpage.h"
#include <QDebug>
#include <QPainter>

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
    singleTextWidth =  fontMetrics().horizontalAdvance(_text);
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
        pb.setFont(painter.font());

        int x = qMin(-i, 0) + windowWidth;

        if(x < windowWidth)
        {
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