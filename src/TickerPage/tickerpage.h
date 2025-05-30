#ifndef TICKERPAGE_H
#define TICKERPAGE_H

#include <QWidget>
#include <QStaticText>
#include <QTimer>
#include <QMap>
#include <QPainter>
#include <qpainter.h>

namespace Ui {
class TickerPage;
}

class TickerPage : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QString separator READ separator WRITE setSeparator)

public:
    TickerPage(QWidget *parent = nullptr, QString text = "");
    virtual ~TickerPage();

public slots:
    QString text() const;
    void setText(QString text);

    void setField(QString key, QString val);

    QString separator() const;
    void setSeparator(QString separator);

protected:
    void paintEvent(QPaintEvent *);

private:
    void updateText();

    // contains keys and values for adding items to the ticker
    QMap<QString, QString> tickerFields;

    // the text used by the ticker
    QString _text;

    // the separator used to seperate each instance of the ticker
    QString _separator;

    // the combined text and separator to be displayed repeatedly
    QStaticText staticText;

    // cycles through the width of the page so the text appears to scroll
    int scrollPos;

    // dimensions of the text and separator
    QSize wholeTextSize;

    // Image object that represents the whole widget
    // QImage image;

    // timer that managed the scrolling of the text
    QTimer* timer;

    // api key for weather
    std::string weatherApiKey;

    // painter for drawing the text
    // QPainter* painter;

private slots:
    virtual void timeout();
};
#endif // TICKERPAGE_H
